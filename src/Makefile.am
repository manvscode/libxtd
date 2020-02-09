#noinst_LIBRARIES = libutility.a

# Add new files in alphabetical order. Thanks.
libutility_sources = base64.c \
					 bytes.c \
					 caesar.c \
					 checksums.c \
					 console.c \
					 endianess.c \
					 exceptions.c \
					 fileio-unix.c \
					 fileio.c \
					 floating-point.c \
					 huffman.c \
					 refobj.c \
					 sort.c \
					 strings.c \
					 time-unix.c \
					 time.c \
					 wstrings.c

libutility_headers = exceptions.h \
					 console.h \
					 utility.h

library_includedir = $(includedir)/libutility/
library_include_HEADERS = $(libutility_headers)

# Library
lib_LTLIBRARIES                           = $(top_builddir)/lib/libutility.la
__top_builddir__lib_libutility_la_SOURCES = $(libutility_sources)
#__top_builddir__lib_libutility_la_LIBADD  = -lcollections

