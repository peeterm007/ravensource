--- junklib.c.orig	2019-08-01 18:36:50 UTC
+++ junklib.c
@@ -33,7 +33,6 @@
 #include <string.h>
 #if HAVE_ICONV
   #ifndef __MINGW32__
-  #define LIBICONV_PLUG
   #endif
   #include <iconv.h>
 #elif HAVE_ICU
