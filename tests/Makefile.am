if ENABLE_TESTS
AM_CFLAGS = -std=c99 -g -ggdb -O0 -I$(top_builddir)/src/  -I/usr/local/include/libutility
#LDFLAGS   = -lm $(top_builddir)/lib/.libs/libutility.a

bin_PROGRAMS = \
$(top_builddir)/bin/test-exceptions \
$(top_builddir)/bin/test-scrambling \
$(top_builddir)/bin/test-huffman \
$(top_builddir)/bin/test-file \
$(top_builddir)/bin/test-observers \
$(top_builddir)/bin/test-fsm \
$(top_builddir)/bin/test-time

__top_builddir__bin_test_exceptions_SOURCES  = test-exceptions.c
__top_builddir__bin_test_exceptions_LDFLAGS  = -lm $(top_builddir)/lib/.libs/libutility.a
__top_builddir__bin_test_scrambling_SOURCES  = test-scrambling.c
__top_builddir__bin_test_scrambling_LDFLAGS  = -lm $(top_builddir)/lib/.libs/libutility.a
__top_builddir__bin_test_huffman_SOURCES     = test-huffman.c
__top_builddir__bin_test_huffman_LDFLAGS     = -lm $(top_builddir)/lib/.libs/libutility.a
__top_builddir__bin_test_file_SOURCES        = test-file.c
__top_builddir__bin_test_file_LDFLAGS        = -lm $(top_builddir)/lib/.libs/libutility.a
__top_builddir__bin_test_observers_SOURCES   = test-observers.c
__top_builddir__bin_test_observers_LDFLAGS   = -lm $(top_builddir)/lib/.libs/libutility.a
__top_builddir__bin_test_fsm_SOURCES         = test-fsm.c
__top_builddir__bin_test_fsm_LDFLAGS         = -lm $(top_builddir)/lib/.libs/libutility.a
__top_builddir__bin_test_time_SOURCES        = test-time.c
__top_builddir__bin_test_time_LDFLAGS        = -lm $(top_builddir)/lib/.libs/libutility.a
endif
