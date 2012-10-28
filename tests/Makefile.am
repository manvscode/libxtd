#AM_CFLAGS = $(DEPS_CFLAGS) -I../src/ -L../src/ -L.

AM_CFLAGS = -std=gnu99 -g -ggdb -O0 -I$(top_builddir)/src/ -L$(top_builddir)/src/ -L$(top_builddir)/lib/.libs/ -L$(top_builddir)/lib/  -I/usr/local/include/libutility -L/usr/local/lib
LDADD     = $(top_builddir)/lib/libutility.la

bin_PROGRAMS = \
$(top_builddir)/bin/test-exceptions \
$(top_builddir)/bin/test-scrambling \
$(top_builddir)/bin/test-huffman 

__top_builddir__bin_test_exceptions_SOURCES  = test-exceptions.c
__top_builddir__bin_test_scrambling_SOURCES  = test-scrambling.c
__top_builddir__bin_test_huffman_SOURCES     = test-huffman.c
