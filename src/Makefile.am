#noinst_LIBRARIES = xtd.a

# Add new files in alphabetical order. Thanks.
xtd_sources = \
			  checksums.c \
			  cmdopt.c \
			  encoding-base64.c \
			  encoding-huffman.c \
			  encryption-aes.c \
			  encryption-caesar.c \
			  endian.c \
			  exceptions.c \
			  filesystem.c \
			  floating-point.c \
			  memory.c \
			  refobj.c \
			  sort.c \
			  string.c \
			  test.c \
			  time.c \
			  wstring.c

if WINDOWS
    xtd_sources += console-windows.c filesystem-windows.c time-windows.c
else # Linux and MacOS X
    xtd_sources += console-unix.c filesystem-unix.c time-unix.c
endif


xtd_headers = \
			  xtd/checksums.h \
			  xtd/cmdopt.h \
			  xtd/console.h \
			  xtd/encoding.h \
			  xtd/encryption.h \
			  xtd/endian.h \
			  xtd/exceptions.h \
			  xtd/filesystem.h \
			  xtd/floating-point.h \
			  xtd/memory.h \
			  xtd/refobj.h \
			  xtd/string.h \
			  xtd/test.h \
			  xtd/time.h \
			  xtd/all.h

library_includedir = $(includedir)/@PACKAGE_NAME@-@PACKAGE_VERSION@/xtd/
library_include_HEADERS = $(xtd_headers)

# Library
lib_LTLIBRARIES                        = $(top_builddir)/lib/libxtd.la
__top_builddir__lib_libxtd_la_SOURCES  = $(xtd_sources)
__top_builddir__lib_libxtd_la_CFLAGS   = -fPIC
__top_builddir__lib_libxtd_la_LDFLAGS  = -no-undefined
#__top_builddir__lib_libxtd_la_LDFLAGS  = -version-info ${VERSION} -no-undefined
__top_builddir__lib_libxtd_la_LIBADD   = -lm

