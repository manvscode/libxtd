#noinst_LIBRARIES = libutility.a

# Add new files in alphabetical order. Thanks.
#libutility_a_SOURCES = bytes.c crash.c exceptions.c fileio.c mime.c

source = bytes.c crash.c exceptions.c fileio.c mime.c
headers = exceptions.h mime.h utility.h

library_includedir = $(includedir)/libutility/
library_include_HEADERS = $(headers)

# Library
lib_LTLIBRARIES = $(top_builddir)/lib/libutility.la 
__top_builddir__lib_libutility_la_SOURCES = $(source)

