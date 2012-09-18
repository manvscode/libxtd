#AM_CFLAGS = $(DEPS_CFLAGS) -I ../src/ -L ../src/ -L .
AM_CFLAGS = -Wall -pedantic -g -ggdb -pg -O0 -D_DEBUG -D_XOPEN_SOURCE -D_XOPEN_SOURCE_EXTENDED -I ../src/ -L ../src/ -L . 
LDADD     = -lutility



bin_PROGRAMS = \
test-exceptions \
test-scrambling 

test_exceptions_SOURCES    = test-exceptions.c
test_scrambling_SOURCES    = test-scrambling.c
