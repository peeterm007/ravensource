--- hw/xfree86/common/xf86Globals.c.orig	2019-02-26 19:28:50 UTC
+++ hw/xfree86/common/xf86Globals.c
@@ -119,7 +119,7 @@ xf86InfoRec xf86Info = {
     .miscModInDevEnabled = TRUE,
     .miscModInDevAllowNonLocal = FALSE,
     .pmFlag = TRUE,
-#if defined(CONFIG_HAL) || defined(CONFIG_UDEV) || defined(CONFIG_WSCONS)
+#if defined(CONFIG_HAL) || defined(CONFIG_UDEV) || defined(CONFIG_WSCONS) || defined(CONFIG_DEVD)
     .forceInputDevices = FALSE,
     .autoAddDevices = TRUE,
     .autoEnableDevices = TRUE,
