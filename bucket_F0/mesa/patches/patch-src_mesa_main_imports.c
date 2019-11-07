--- src/mesa/main/imports.c.orig	2019-10-24 16:13:04 UTC
+++ src/mesa/main/imports.c
@@ -83,11 +83,15 @@ void *
 _mesa_align_malloc(size_t bytes, unsigned long alignment)
 {
 #if defined(HAVE_POSIX_MEMALIGN)
+# ifdef __sun__
+   return memalign(alignment, bytes);
+# else
    void *mem;
    int err = posix_memalign(& mem, alignment, bytes);
    if (err)
       return NULL;
    return mem;
+# endif
 #elif defined(_WIN32)
    return _aligned_malloc(bytes, alignment);
 #else