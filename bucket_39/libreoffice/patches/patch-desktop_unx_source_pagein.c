--- desktop/unx/source/pagein.c.orig	2019-09-18 14:12:06 UTC
+++ desktop/unx/source/pagein.c
@@ -25,7 +25,9 @@
 #include <stdio.h>
 #include <string.h>
 #include <sys/stat.h>
+#ifdef LINUX
 #include <sys/sysmacros.h>
+#endif
 #include <sys/types.h>
 
 /* do_pagein */
