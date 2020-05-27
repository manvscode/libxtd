if ENABLE_TESTS
AM_CFLAGS = -std=c99 -g -ggdb -O0 -I$(top_builddir)/src/  -I ../src/
#LDFLAGS   = -lm $(top_builddir)/lib/libxtd.la

bin_PROGRAMS = \
$(top_builddir)/bin/test-base64 \
$(top_builddir)/bin/test-bytes \
$(top_builddir)/bin/test-console \
$(top_builddir)/bin/test-dir \
$(top_builddir)/bin/test-exceptions \
$(top_builddir)/bin/test-file \
$(top_builddir)/bin/test-huffman \
$(top_builddir)/bin/test-scrambling \
$(top_builddir)/bin/test-time

__top_builddir__bin_test_bytes_SOURCES       = test-bytes.c
__top_builddir__bin_test_bytes_LDFLAGS       = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_console_SOURCES     = test-console.c
__top_builddir__bin_test_console_LDFLAGS     = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_exceptions_SOURCES  = test-exceptions.c
__top_builddir__bin_test_exceptions_LDFLAGS  = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_scrambling_SOURCES  = test-scrambling.c
__top_builddir__bin_test_scrambling_LDFLAGS  = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_file_SOURCES        = test-file.c
__top_builddir__bin_test_file_LDFLAGS        = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_dir_SOURCES         = test-dir.c
__top_builddir__bin_test_dir_LDFLAGS         = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_huffman_SOURCES     = test-huffman.c
__top_builddir__bin_test_huffman_LDFLAGS     = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_time_SOURCES        = test-time.c
__top_builddir__bin_test_time_LDFLAGS        = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_base64_SOURCES      = test-base64.c
__top_builddir__bin_test_base64_LDFLAGS      = -lm $(top_builddir)/lib/libxtd.la
endif
