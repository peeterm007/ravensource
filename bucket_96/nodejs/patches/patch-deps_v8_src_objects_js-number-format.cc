https://github.com/nodejs/node/issues/32660

--- deps/v8/src/objects/js-number-format.cc.orig	2020-03-26 20:00:01 UTC
+++ deps/v8/src/objects/js-number-format.cc
@@ -1187,42 +1187,31 @@ MaybeHandle<JSNumberFormat> JSNumberFormat::New(Isolat
 }
 
 namespace {
-Maybe<icu::UnicodeString> IcuFormatNumber(
+Maybe<bool> IcuFormatNumber(
     Isolate* isolate,
     const icu::number::LocalizedNumberFormatter& number_format,
-    Handle<Object> numeric_obj, icu::FieldPositionIterator* fp_iter) {
+    Handle<Object> numeric_obj, icu::number::FormattedNumber* formatted) {
   // If it is BigInt, handle it differently.
   UErrorCode status = U_ZERO_ERROR;
-  icu::number::FormattedNumber formatted;
   if (numeric_obj->IsBigInt()) {
     Handle<BigInt> big_int = Handle<BigInt>::cast(numeric_obj);
     Handle<String> big_int_string;
     ASSIGN_RETURN_ON_EXCEPTION_VALUE(isolate, big_int_string,
                                      BigInt::ToString(isolate, big_int),
-                                     Nothing<icu::UnicodeString>());
-    formatted = number_format.formatDecimal(
+                                     Nothing<bool>());
+    *formatted = number_format.formatDecimal(
         {big_int_string->ToCString().get(), big_int_string->length()}, status);
   } else {
     double number = numeric_obj->Number();
-    formatted = number_format.formatDouble(number, status);
+    *formatted = number_format.formatDouble(number, status);
   }
   if (U_FAILURE(status)) {
     // This happen because of icu data trimming trim out "unit".
     // See https://bugs.chromium.org/p/v8/issues/detail?id=8641
-    THROW_NEW_ERROR_RETURN_VALUE(isolate,
-                                 NewTypeError(MessageTemplate::kIcuError),
-                                 Nothing<icu::UnicodeString>());
+    THROW_NEW_ERROR_RETURN_VALUE(
+        isolate, NewTypeError(MessageTemplate::kIcuError), Nothing<bool>());
   }
-  if (fp_iter) {
-    formatted.getAllFieldPositions(*fp_iter, status);
-  }
-  icu::UnicodeString result = formatted.toString(status);
-  if (U_FAILURE(status)) {
-    THROW_NEW_ERROR_RETURN_VALUE(isolate,
-                                 NewTypeError(MessageTemplate::kIcuError),
-                                 Nothing<icu::UnicodeString>());
-  }
-  return Just(result);
+  return Just(true);
 }
 
 }  // namespace
@@ -1233,10 +1222,16 @@ MaybeHandle<String> JSNumberFormat::FormatNumeric(
     Handle<Object> numeric_obj) {
   DCHECK(numeric_obj->IsNumeric());
 
-  Maybe<icu::UnicodeString> maybe_format =
-      IcuFormatNumber(isolate, number_format, numeric_obj, nullptr);
+  icu::number::FormattedNumber formatted;
+  Maybe<bool> maybe_format =
+      IcuFormatNumber(isolate, number_format, numeric_obj, &formatted);
   MAYBE_RETURN(maybe_format, Handle<String>());
-  return Intl::ToString(isolate, maybe_format.FromJust());
+  UErrorCode status = U_ZERO_ERROR;
+  icu::UnicodeString result = formatted.toString(status);
+  if (U_FAILURE(status)) {
+    THROW_NEW_ERROR(isolate, NewTypeError(MessageTemplate::kIcuError), String);
+  }
+  return Intl::ToString(isolate, result);
 }
 
 namespace {
@@ -1349,12 +1344,18 @@ std::vector<NumberFormatSpan> FlattenRegionsToParts(
 }
 
 namespace {
-Maybe<int> ConstructParts(Isolate* isolate, const icu::UnicodeString& formatted,
-                          icu::FieldPositionIterator* fp_iter,
+Maybe<int> ConstructParts(Isolate* isolate,
+                          icu::number::FormattedNumber* formatted,
                           Handle<JSArray> result, int start_index,
                           Handle<Object> numeric_obj, bool style_is_unit) {
+  UErrorCode status = U_ZERO_ERROR;
+  icu::UnicodeString formatted_text = formatted->toString(status);
+  if (U_FAILURE(status)) {
+    THROW_NEW_ERROR_RETURN_VALUE(
+        isolate, NewTypeError(MessageTemplate::kIcuError), Nothing<int>());
+  }
   DCHECK(numeric_obj->IsNumeric());
-  int32_t length = formatted.length();
+  int32_t length = formatted_text.length();
   int index = start_index;
   if (length == 0) return Just(index);
 
@@ -1363,13 +1364,14 @@ Maybe<int> ConstructParts(Isolate* isolate, const icu:
   // other region covers some part of the formatted string. It's possible
   // there's another field with exactly the same begin and end as this backdrop,
   // in which case the backdrop's field_id of -1 will give it lower priority.
-  regions.push_back(NumberFormatSpan(-1, 0, formatted.length()));
+  regions.push_back(NumberFormatSpan(-1, 0, formatted_text.length()));
 
   {
-    icu::FieldPosition fp;
-    while (fp_iter->next(fp)) {
-      regions.push_back(NumberFormatSpan(fp.getField(), fp.getBeginIndex(),
-                                         fp.getEndIndex()));
+    icu::ConstrainedFieldPosition cfp;
+    cfp.constrainCategory(UFIELD_CATEGORY_NUMBER);
+    while (formatted->nextPosition(cfp, status)) {
+      regions.push_back(
+          NumberFormatSpan(cfp.getField(), cfp.getStart(), cfp.getLimit()));
     }
   }
 
@@ -1391,7 +1393,7 @@ Maybe<int> ConstructParts(Isolate* isolate, const icu:
     Handle<String> substring;
     ASSIGN_RETURN_ON_EXCEPTION_VALUE(
         isolate, substring,
-        Intl::ToString(isolate, formatted, part.begin_pos, part.end_pos),
+        Intl::ToString(isolate, formatted_text, part.begin_pos, part.end_pos),
         Nothing<int>());
     Intl::AddElement(isolate, result, index, field_type_string, substring);
     ++index;
@@ -1411,14 +1413,14 @@ MaybeHandle<JSArray> JSNumberFormat::FormatToParts(
       number_format->icu_number_formatter().raw();
   CHECK_NOT_NULL(fmt);
 
-  icu::FieldPositionIterator fp_iter;
-  Maybe<icu::UnicodeString> maybe_format =
-      IcuFormatNumber(isolate, *fmt, numeric_obj, &fp_iter);
+  icu::number::FormattedNumber formatted;
+  Maybe<bool> maybe_format =
+      IcuFormatNumber(isolate, *fmt, numeric_obj, &formatted);
   MAYBE_RETURN(maybe_format, Handle<JSArray>());
 
   Handle<JSArray> result = factory->NewJSArray(0);
   Maybe<int> maybe_format_to_parts = ConstructParts(
-      isolate, maybe_format.FromJust(), &fp_iter, result, 0, numeric_obj,
+      isolate, &formatted, result, 0, numeric_obj,
       number_format->style() == JSNumberFormat::Style::UNIT);
   MAYBE_RETURN(maybe_format_to_parts, Handle<JSArray>());
 
