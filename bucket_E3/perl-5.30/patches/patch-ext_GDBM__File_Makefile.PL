--- ext/GDBM_File/Makefile.PL.orig	2019-10-24 20:18:04 UTC
+++ ext/GDBM_File/Makefile.PL
@@ -7,6 +7,7 @@ WriteMakefile(
     VERSION_FROM => 'GDBM_File.pm',
     realclean => {FILES=> 'const-c.inc const-xs.inc'},
     XS_VERSION => eval MM->parse_version('GDBM_File.pm'), #silence warnings if we are a dev release
+    dynamic_lib => { OTHERLDFLAGS => "-Wl,-rpath,@PREFIX@/lib" },
 );
 WriteConstants(
     NAME => 'GDBM_File',
