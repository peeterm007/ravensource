--- src/unix/fs.c.orig	2019-08-09 14:57:12 UTC
+++ src/unix/fs.c
@@ -889,7 +889,6 @@ static ssize_t uv__fs_sendfile(uv_fs_t*
 static ssize_t uv__fs_utime(uv_fs_t* req) {
 #if defined(__linux__)                                                         \
     || defined(_AIX71)                                                         \
-    || defined(__sun)                                                          \
     || defined(__HAIKU__)
   /* utimesat() has nanosecond resolution but we stick to microseconds
    * for the sake of consistency with other platforms.
@@ -901,6 +900,7 @@ static ssize_t uv__fs_utime(uv_fs_t* req
   ts[1].tv_nsec = (uint64_t)(req->mtime * 1000000) % 1000000 * 1000;
   return utimensat(AT_FDCWD, req->path, ts, 0);
 #elif defined(__APPLE__)                                                      \
+    || defined(__sun)                                                         \
     || defined(__DragonFly__)                                                 \
     || defined(__FreeBSD__)                                                   \
     || defined(__FreeBSD_kernel__)                                            \
