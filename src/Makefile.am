#noinst_LIBRARIES = libutility.a

# Add new files in alphabetical order. Thanks.
libutility_sources = base64.c \
					 bytes.c \
					 caesar.c \
					 checksums.c \
					 console.c \
					 endianess.c \
					 exceptions.c \
					 fileio.c \
					 floating-point.c \
					 huffman.c \
					 refobj.c \
					 sort.c \
					 strings.c \
					 time.c \
					 wstrings.c

if WINDOWS
    libutility_sources += fileio-windows.c time-windows.c
else # Linux and MacOS X
    libutility_sources += fileio-unix.c time-unix.c
endif


libutility_headers = exceptions.h \
					 console.h \
					 utility.h

library_includedir = $(includedir)/@PACKAGE_NAME@-@PACKAGE_VERSION@/
library_include_HEADERS = $(libutility_headers)

# Library
lib_LTLIBRARIES                           = $(top_builddir)/lib/libutility.la
__top_builddir__lib_libutility_la_SOURCES = $(libutility_sources)
__top_builddir__lib_libutility_la_LIBADD  = -lm

