--- src/diffviewer/ydiff.c.orig	2020-01-01 15:52:34 UTC
+++ src/diffviewer/ydiff.c
@@ -817,7 +817,7 @@ dff_execute (const char *args, const cha
     /* escape potential $ to avoid shell variable substitutions in popen() */
     file1_esc = strutils_shell_escape (file1);
     file2_esc = strutils_shell_escape (file2);
-    cmd = g_strdup_printf ("diff %s %s %s %s %s", args, extra, opt, file1_esc, file2_esc);
+    cmd = g_strdup_printf ("gdiff %s %s %s %s %s", args, extra, opt, file1_esc, file2_esc);
     g_free (file1_esc);
     g_free (file2_esc);
 
