--- src/sna/sna_threads.c.orig	2018-12-03 09:01:25 UTC
+++ src/sna/sna_threads.c
@@ -29,6 +29,9 @@
 #include "config.h"
 #endif
 
+#define _WITH_GETLINE	/* to expose getline() in stdio.h on FreeBSD */
+#include <stdio.h>	/* for getline() */
+
 #include "sna.h"
 
 #include <unistd.h>
