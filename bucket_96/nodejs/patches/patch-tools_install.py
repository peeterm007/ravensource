--- tools/install.py.orig	2020-05-05 17:48:10 UTC
+++ tools/install.py
@@ -151,7 +151,7 @@ def files(action):
   action(['deps/v8/tools/gdbinit'], 'share/doc/node/')
   action(['deps/v8/tools/lldb_commands.py'], 'share/doc/node/')
 
-  if 'freebsd' in sys.platform or 'openbsd' in sys.platform:
+  if 'skipme' in sys.platform:
     action(['doc/node.1'], 'man/man1/')
   else:
     action(['doc/node.1'], 'share/man/man1/')
