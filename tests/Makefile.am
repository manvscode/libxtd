if ENABLE_TESTS
AM_CFLAGS = -Wall -pedantic -static -I$(top_builddir)/src/

bin_PROGRAMS = \
$(top_builddir)/bin/test-all \
$(top_builddir)/bin/test-base64 \
$(top_builddir)/bin/test-bytes \
$(top_builddir)/bin/test-console \
$(top_builddir)/bin/test-dir \
$(top_builddir)/bin/test-exceptions \
$(top_builddir)/bin/test-file \
$(top_builddir)/bin/test-huffman \
$(top_builddir)/bin/test-scrambling \
\
$(top_builddir)/bin/test-checksums \
$(top_builddir)/bin/test-cmdopt \
$(top_builddir)/bin/test-encoding \
$(top_builddir)/bin/test-encryption \
$(top_builddir)/bin/test-endian \
$(top_builddir)/bin/test-filesystem \
$(top_builddir)/bin/test-floating-point \
$(top_builddir)/bin/test-memory \
$(top_builddir)/bin/test-refobj \
$(top_builddir)/bin/test-string \
$(top_builddir)/bin/test-time

__top_builddir__bin_test_all_LDFLAGS         = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_all_SOURCES         = test-all.c \
											   test-checksums.c \
											   test-cmdopt.c \
											   test-encoding.c \
											   test-encryption.c \
											   test-endian.c \
											   test-filesystem.c \
											   test-floating-point.c \
											   test-memory.c \
											   test-refobj.c \
											   test-string.c \
											   test-time.c
__top_builddir__bin_test_base64_LDFLAGS      = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_base64_SOURCES      = test-base64.c
__top_builddir__bin_test_bytes_LDFLAGS       = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_bytes_SOURCES       = test-bytes.c


__top_builddir__bin_test_console_LDFLAGS     = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_console_SOURCES     = test-console.c
__top_builddir__bin_test_dir_LDFLAGS         = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_dir_SOURCES         = test-dir.c
__top_builddir__bin_test_exceptions_LDFLAGS  = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_exceptions_SOURCES  = test-exceptions.c
__top_builddir__bin_test_file_LDFLAGS        = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_file_SOURCES        = test-file.c
__top_builddir__bin_test_huffman_LDFLAGS     = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_huffman_SOURCES     = test-huffman.c
__top_builddir__bin_test_scrambling_LDFLAGS  = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_scrambling_SOURCES  = test-scrambling.c

__top_builddir__bin_test_checksums_CFLAGS       = -DTEST_CHECKSUMS -static
__top_builddir__bin_test_checksums_LDFLAGS      = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_checksums_SOURCES      = test-checksums.c
__top_builddir__bin_test_cmdopt_CFLAGS          = -DTEST_CMDOPT -static
__top_builddir__bin_test_cmdopt_LDFLAGS         = -static -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_cmdopt_SOURCES         = test-cmdopt.c
__top_builddir__bin_test_encoding_CFLAGS        = -DTEST_ENCODING -static
__top_builddir__bin_test_encoding_LDFLAGS       = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_encoding_SOURCES       = test-encoding.c
__top_builddir__bin_test_encryption_CFLAGS      = -DTEST_ENCRYPTION -static
__top_builddir__bin_test_encryption_LDFLAGS     = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_encryption_SOURCES     = test-encryption.c
__top_builddir__bin_test_endian_CFLAGS          = -DTEST_ENDIAN -static
__top_builddir__bin_test_endian_LDFLAGS         = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_endian_SOURCES         = test-endian.c
__top_builddir__bin_test_filesystem_CFLAGS      = -DTEST_FILESYSTEM -static
__top_builddir__bin_test_filesystem_LDFLAGS     = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_filesystem_SOURCES     = test-filesystem.c
__top_builddir__bin_test_floating_point_CFLAGS  = -DTEST_FLOATING_POINT -static
__top_builddir__bin_test_floating_point_LDFLAGS = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_floating_point_SOURCES = test-floating-point.c
__top_builddir__bin_test_memory_CFLAGS          = -DTEST_MEMORY -static
__top_builddir__bin_test_memory_LDFLAGS         = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_memory_SOURCES         = test-memory.c
__top_builddir__bin_test_refobj_CFLAGS          = -DTEST_REFOBJ -static
__top_builddir__bin_test_refobj_LDFLAGS         = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_refobj_SOURCES         = test-refobj.c
__top_builddir__bin_test_string_CFLAGS          = -DTEST_STRING -static
__top_builddir__bin_test_string_LDFLAGS         = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_string_SOURCES         = test-string.c
__top_builddir__bin_test_time_CFLAGS            = -DTEST_TIME -static
__top_builddir__bin_test_time_LDFLAGS           = -lm $(top_builddir)/lib/libxtd.la
__top_builddir__bin_test_time_SOURCES           = test-time.c
endif
