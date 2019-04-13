AC_INIT([libutility], [0.2], [manvscode@gmail.com], [libutility], [http://www.manvscode.com/])
AM_INIT_AUTOMAKE([1.13 foreign silent-rules -Wall -Werror])

AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([src/libutility-config.h])

AC_PROG_CC
AC_PROG_CC_STDC
AC_C_INLINE
AC_HEADER_STDC

AH_TOP([
#ifndef _LIBUTILITY_CONFIG_H_
#define _LIBUTILITY_CONFIG_H_
])
AH_BOTTOM([
#endif /* _LIBUTILITY_CONFIG_H_ */
])

# If big endian define WORDS_BIGENDIAN
AC_C_BIGENDIAN

#CFLAGS="-std=c11 -Wall -pedantic -fsanitize=undefined -g -ggdb -O0 -DDEBUG -I/usr/local/include/"
CFLAGS="$CFLAGS"
LDFLAGS="$LDFLAGS -lm"

AM_PROG_AR

LT_INIT([shared static])
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

AC_PROG_INSTALL

echo " ------------------------------ "
echo ""
echo "  CFLAGS = $CFLAGS"
echo " LDFLAGS = $LDFLAGS"
echo ""
echo " ------------------------------ "

AC_ARG_ENABLE([tests],
	[AS_HELP_STRING([--disable-tests], [Enable test programs.])],
	[:],
	[enable_tests=no])

AM_CONDITIONAL([ENABLE_TESTS], [test "$enable_tests" = "yes"])


AC_CONFIG_FILES([
	Makefile
	src/Makefile
	tests/Makefile
])

AC_OUTPUT
