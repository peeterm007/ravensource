--- ucb/source/ucp/webdav/DateTimeHelper.cxx.orig	2019-09-18 14:12:06 UTC
+++ ucb/source/ucp/webdav/DateTimeHelper.cxx
@@ -17,6 +17,8 @@
  *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
  */
 
+#include <cstdio>
+
 #include <osl/time.h>
 #include <com/sun/star/util/DateTime.hpp>
 #include "DateTimeHelper.hxx"
