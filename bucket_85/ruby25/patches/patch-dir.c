--- dir.c.orig	2020-03-31 12:15:56 UTC
+++ dir.c
@@ -119,16 +119,16 @@ char *strchr(char*,char);
 # define USE_NAME_ON_FS 0
 #endif
 
-#ifdef __APPLE__
+#if 0
 # define NORMALIZE_UTF8PATH 1
 #else
 # define NORMALIZE_UTF8PATH 0
 #endif
 
+#include <sys/vnode.h>
 #if NORMALIZE_UTF8PATH
 #include <sys/param.h>
 #include <sys/mount.h>
-#include <sys/vnode.h>
 
 # if defined HAVE_FGETATTRLIST || !defined HAVE_GETATTRLIST
 #   define need_normalization(dirp, path) need_normalization(dirp)
@@ -1126,7 +1126,7 @@ rb_dir_getwd_ospath(void)
     path_guard = Data_Wrap_Struct((VALUE)0, NULL, RUBY_DEFAULT_FREE, NULL);
     path = ruby_getcwd();
     DATA_PTR(path_guard) = path;
-#ifdef __APPLE__
+#if NORMALIZE_UTF8PATH
     cwd = rb_str_normalize_ospath(path, strlen(path));
     OBJ_TAINT(cwd);
 #else
