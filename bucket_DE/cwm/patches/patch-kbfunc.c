--- kbfunc.c.orig	2018-05-14 13:31:34 UTC
+++ kbfunc.c
@@ -28,7 +28,11 @@
 #include <err.h>
 #include <errno.h>
 #include <limits.h>
+#ifdef __sun__
+#define _PATH_DEFPATH "/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/raven/bin:/usr/raven/sbin"
+#else
 #include <paths.h>
+#endif
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
@@ -589,6 +593,9 @@ kbfunc_menu_exec(void *ctx, struct cargs
 	struct menu_q		 menuq;
 	int			 l, i;
 	int			 mflags = (CWM_MENU_DUMMY | CWM_MENU_FILE);
+#ifdef __sun__
+	struct stat		s;
+#endif
 
 	TAILQ_INIT(&menuq);
 
@@ -613,7 +620,12 @@ kbfunc_menu_exec(void *ctx, struct cargs
 			if (l == -1 || l >= sizeof(tpath))
 				continue;
 			/* Skip everything but regular files and symlinks. */
+#ifdef __sun__
+			stat(dp->d_name, &s);
+			if (s.st_mode != S_IFDIR && s.st_mode != S_IFLNK) {
+#else
 			if (dp->d_type != DT_REG && dp->d_type != DT_LNK) {
+#endif
 				/* lstat(2) in case d_type isn't supported. */
 				if (lstat(tpath, &sb) == -1)
 					continue;