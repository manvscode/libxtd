#noinst_LIBRARIES = libutility.a

# Add new files in alphabetical order. Thanks.
libutility_sources = bytes.c \
					 base64.c \
					 caesar.c \
					 checksums.c \
					 endianess.c \
					 exceptions.c \
					 fileio.c \
					 fileio-unix.c \
					 huffman.c \
					 strings.c \
					 console.c \
					 time.c \
					 time-unix.c \
					 sort.c \
					 refobj.c

libutility_headers = exceptions.h \
					 utility.h

library_includedir = $(includedir)/libutility/
library_include_HEADERS = $(libutility_headers)

# Library
lib_LTLIBRARIES                           = $(top_builddir)/lib/libutility.la
__top_builddir__lib_libutility_la_SOURCES = $(libutility_sources)
#__top_builddir__lib_libutility_la_LIBADD  = -lcollections

