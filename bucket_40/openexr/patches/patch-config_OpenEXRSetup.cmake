--- config/OpenEXRSetup.cmake.orig	2020-05-11 15:53:42 UTC
+++ config/OpenEXRSetup.cmake
@@ -42,10 +42,6 @@ set(OPENEXR_OUTPUT_SUBDIR OpenEXR CACHE
 # but is pretty harmless to set globally
 set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
-# Suffix for debug configuration libraries
-# (if you should choose to install those)
-set(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "Suffix for debug builds")
-
 # Usual cmake option to build shared libraries or not
 option(BUILD_SHARED_LIBS "Build shared library" ON)
 # This allows a "double library" setup, where we compile both
