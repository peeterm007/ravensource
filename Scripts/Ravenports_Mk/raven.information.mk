# RESERVED_WARNING
# This file is not directly used by the Raven framework.
# It's sole purpose is to provide definitions that multiple specifications
# need in a single location.  The data is extracted by using the
# EXTRACT_INFO function on a specification definition, e.g.
#
# DEF[PORTVERSION]=		EXTRACT_INFO(GCC8_VERSION)
# 
# This file is only used at "compile-time", that is when the port
# specification is used to generate the buildsheet.

# ------------------------------------------------------------------------
# APQ
# ------------------------------------------------------------------------

APQ_VERSION=			3.2.0
APQ_BASE_REVISION=		0
APQ_MYSQL_REVISION=		0
APQ_PGSQL_REVISION=		0
APQ_ODBC_REVISION=		0

# ------------------------------------------------------------------------
# boost
# ------------------------------------------------------------------------

BOOST_VERSION=			1.72.0
BOOST_JAM_REVISION=		0
BOOST_LIBRARIES_REVISION=	0

# ------------------------------------------------------------------------
# Only keep one closed branch of gcc
# As of 6 APR 2020, gcc 7.5 closed the branch on 14-NOV-2019
# That leaves gcc7, gcc8, gcc9, and the gcc10 (upcoming)
# ------------------------------------------------------------------------
# gcc7
# ------------------------------------------------------------------------

GCC7_BRANCH=			7
GCC7_POINT=			5.0
GCC7_VERSION=			${GCC7_BRANCH}.${GCC7_POINT}
GCC7_SNAPSHOT=			20191114
GCC7_BUILD_RELEASE=		yes
GCC7_REVISION=			0
GCC7_GNAT_UTIL_REVISION=	0
GCC7_GNATCROSS_REVISION=	0
GCC7_BOOTSTRAP_REVISION=	0

.if ${GCC7_BUILD_RELEASE:Mno}
GCC7_PORTVERSION=		${GCC7_BRANCH}.${GCC7_SNAPSHOT}
GCC7_IDENTIFICATION=		gcc-${GCC7_BRANCH}-${GCC7_SNAPSHOT}
GCC7_MS_SUBDIR=			snapshots/${GCC7_BRANCH}-${GCC7_SNAPSHOT}
GCC7_PHASE=			snapshot
.else
GCC7_PORTVERSION=		${GCC7_VERSION}
GCC7_IDENTIFICATION=		gcc-${GCC7_VERSION}
GCC7_MS_SUBDIR=			releases/gcc-${GCC7_VERSION}
GCC7_PHASE=			release
.endif

# ------------------------------------------------------------------------
# gcc8
# ------------------------------------------------------------------------

GCC8_BRANCH=			8
GCC8_POINT=			4.0
GCC8_VERSION=			${GCC8_BRANCH}.${GCC8_POINT}
GCC8_SNAPSHOT=			20200420
GCC8_BUILD_RELEASE=		yes
GCC8_REVISION=			0
GCC8_GNAT_UTIL_REVISION=	0
GCC8_GNATCROSS_REVISION=	0
GCC8_BOOTSTRAP_REVISION=	0

.if ${GCC8_BUILD_RELEASE:Mno}
GCC8_PORTVERSION=		${GCC8_BRANCH}.${GCC8_SNAPSHOT}
GCC8_IDENTIFICATION=		gcc-${GCC8_BRANCH}-${GCC8_SNAPSHOT}
GCC8_MS_SUBDIR=			snapshots/${GCC8_BRANCH}-${GCC8_SNAPSHOT}
GCC8_PHASE=			snapshot
.else
GCC8_PORTVERSION=		${GCC8_VERSION}
GCC8_IDENTIFICATION=		gcc-${GCC8_VERSION}
GCC8_MS_SUBDIR=			releases/gcc-${GCC8_VERSION}
GCC8_PHASE=			release
.endif

# ------------------------------------------------------------------------
# gcc9
# ------------------------------------------------------------------------

GCC9_BRANCH=			9
GCC9_POINT=			3.0
GCC9_VERSION=			${GCC9_BRANCH}.${GCC9_POINT}
GCC9_SNAPSHOT=			20200312
GCC9_BUILD_RELEASE=		yes
GCC9_REVISION=			0
GCC9_GNAT_UTIL_REVISION=	0
GCC9_GNATCROSS_REVISION=	0
GCC9_BOOTSTRAP_REVISION=	0

.if ${GCC9_BUILD_RELEASE:Mno}
GCC9_PORTVERSION=		${GCC9_BRANCH}.${GCC9_SNAPSHOT}
GCC9_IDENTIFICATION=		gcc-${GCC9_BRANCH}-${GCC9_SNAPSHOT}
GCC9_MS_SUBDIR=			snapshots/${GCC9_BRANCH}-${GCC9_SNAPSHOT}
GCC9_PHASE=			snapshot
.else
GCC9_PORTVERSION=		${GCC9_VERSION}
GCC9_IDENTIFICATION=		gcc-${GCC9_VERSION}
GCC9_MS_SUBDIR=			releases/gcc-${GCC9_VERSION}
GCC9_PHASE=			release
.endif

# ------------------------------------------------------------------------
# icu
# ------------------------------------------------------------------------

ICU_VERSION=			67.1
ICU_REVISION=			0
ICU_LX_REVISION=		0

# ------------------------------------------------------------------------
# libxml2
# ------------------------------------------------------------------------

LIBXML2_VERSION=		2.9.10
LIBXML2_REVISION=		0
LIBXML2_PYTHON_REVISION=	0

# ------------------------------------------------------------------------
# libxslt
# ------------------------------------------------------------------------

LIBXSLT_VERSION=		1.1.34
LIBXSLT_REVISION=		0
LIBXSLT_PYTHON_REVISION=	0

# ------------------------------------------------------------------------
# ruby
# ------------------------------------------------------------------------

RUBY_2.5_REVISION=		3
RUBY_2.5_PATCHLEVEL=		0

RUBY_2.6_REVISION=		3
RUBY_2.6_PATCHLEVEL=		0

RUBY_2.7_REVISION=		2
RUBY_2.7_PATCHLEVEL=		0

# ------------------------------------------------------------------------
# gnome
# ------------------------------------------------------------------------

GTK2_VERSION=			2.10.0
GTK3_VERSION=			3.0.0
GTK2_PORT_VERSION=		2.24.32
GTK3_PORT_VERSION=		3.24.20

# ------------------------------------------------------------------------
# default gcc and binutils
# ------------------------------------------------------------------------

CURRENT_GCC=			gcc9	# mirror in Uses/meson.mk
CURRENT_GCC_VERSION=		${GCC9_VERSION}
BINUTILS_VERSION=		2.34

# ------------------------------------------------------------------------
# aspell
# ------------------------------------------------------------------------

ASPELL_CORE_VERSION=		0.60.8
ASPELL_INSTALL_VERSION=		${ASPELL_CORE_VERSION:R}

# ------------------------------------------------------------------------
# apr1 and other apache projects
# ------------------------------------------------------------------------

APR1_VERSION=			1.7.0
APR1_UTIL_VERSION=		1.6.1
SUBVERSION_VERSION=		1.13.0

# ------------------------------------------------------------------------
# Miscellaneous master versions
# ------------------------------------------------------------------------

LIBFM_VERSION=			1.3.1
LIBTOOL_VERSION=		2.4.6
FREI0R_VERSION=			1.7.0
M17N_VERSION=			1.8.0
GLIBC_VERSION=			2.26
GSTREAMER1_VERSION=		1.16.2		# only even (1.16.x, 1.18.x)
GSTREAMER1_GST=			1.0
GSTREAMER1_SOVERSION=		0.1602.0
XORG_VERSION=			7.7
FIREFOX52_VERSION=		52.9.0
FIREFOX_ESR_VERSION=		68.8.0
FIREFOX_VERSION=		76.0.1
LLVM_VERSION=			10.0.0
ZLIB_VERSION=			1.2.11
OPENEXR_VERSION=		2.5.1
GHOSTSCRIPT_VERSION=		9.52

# ------------------------------------------------------------------------
# Gnatcross options
# ------------------------------------------------------------------------

GNATCROSS_FREEBSD_11=		11.3
GNATCROSS_FREEBSD_12=		12.0

# ------------------------------------------------------------------------
# Qt and Lumina versions
# ------------------------------------------------------------------------

QT5_VERSION=			5.14.2
LUMINA_VERSION=			1.6.0
LUMINA_RELEASE_TAG=		1.6.0
