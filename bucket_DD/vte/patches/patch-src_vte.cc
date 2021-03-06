--- src/vte.cc.orig	2020-03-26 17:22:26 UTC
+++ src/vte.cc
@@ -29,6 +29,13 @@
 #ifdef HAVE_SYS_TERMIOS_H
 #include <sys/termios.h>
 #endif
+#ifdef HAVE_TERMIOS_H
+#include <termios.h>
+#endif
+#if defined(__sun__)
+#include <sys/ioccom.h>
+#include <sys/ptyvar.h>
+#endif
 
 #include <glib.h>
 #include <glib-unix.h>
@@ -3963,6 +3970,9 @@ Terminal::pty_io_read(int const fd,
 			bp = chunk->data + chunk->len;
 			len = 0;
 			do {
+#ifdef __sun__
+				int ret = read (fd, bp, rem);
+#else
                                 /* We'd like to read (fd, bp, rem); but due to TIOCPKT mode
                                  * there's an extra input byte returned at the beginning.
                                  * We need to see what that byte is, but otherwise drop it
@@ -3974,6 +3984,7 @@ Terminal::pty_io_read(int const fd,
                                 int ret = read (fd, bp - 1, rem + 1);
                                 pkt_header = bp[-1];
                                 bp[-1] = save;
+#endif
 				switch (ret){
 					case -1:
 						err = errno;
@@ -3982,6 +3993,7 @@ Terminal::pty_io_read(int const fd,
 						eos = true;
 						goto out;
 					default:
+#ifndef __sun__
                                                 ret--;
 
                                                 if (pkt_header == TIOCPKT_DATA) {
@@ -4008,6 +4020,7 @@ Terminal::pty_io_read(int const fd,
                                                         if (pkt_header & TIOCPKT_START) {
                                                                 pty_scroll_lock_changed(false);
                                                         }
+#endif
                                                 }
 						break;
 				}
