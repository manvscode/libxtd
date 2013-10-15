if ENABLE_TESTS
AM_CFLAGS = -std=gnu99 -g -ggdb -O0 -I$(top_builddir)/src/  -I/usr/local/include/libutility
LDADD     = $(top_builddir)/lib/libutility.la

bin_PROGRAMS = \
$(top_builddir)/bin/test-exceptions \
$(top_builddir)/bin/test-scrambling \
$(top_builddir)/bin/test-huffman \
$(top_builddir)/bin/test-file \
$(top_builddir)/bin/test-observers \
$(top_builddir)/bin/test-fsm

__top_builddir__bin_test_exceptions_SOURCES  = test-exceptions.c
__top_builddir__bin_test_scrambling_SOURCES  = test-scrambling.c
__top_builddir__bin_test_huffman_SOURCES     = test-huffman.c
__top_builddir__bin_test_file_SOURCES        = test-file.c
__top_builddir__bin_test_observers_SOURCES   = test-observers.c
__top_builddir__bin_test_fsm_SOURCES         = test-fsm.c
endif
