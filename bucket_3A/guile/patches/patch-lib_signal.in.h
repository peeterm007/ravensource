--- lib/signal.in.h.orig	2018-09-04 08:40:19 UTC
+++ lib/signal.in.h
@@ -60,6 +60,7 @@
    But avoid namespace pollution on glibc systems.*/
 #if (@GNULIB_PTHREAD_SIGMASK@ || defined GNULIB_POSIXCHECK) \
     && ((defined __APPLE__ && defined __MACH__) \
+	|| defined __DragonFly__ \
         || defined __FreeBSD__ || defined __OpenBSD__ || defined __osf__ \
         || defined __sun || defined __ANDROID__) \
     && ! defined __GLIBC__
