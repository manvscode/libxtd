AC_INIT([libutility], [0.1], [manvscode@gmail.com], [libutility], [http://www.shrewdcreative.com/])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AM_SILENT_RULES([yes])
AC_PROG_CC
AC_PROG_CC_C99
dnlAC_C_INLINE

AC_HEADER_STDC


CFLAGS=" -Wall -pedantic -g -ggdb -pg -O0 -D_DEBUG -I../../libcollections/src/ -lcollections"
dnl CFLAGS=" -Wall -pedantic -O3  -lcollections"
LDFLAGS=""

AC_PROG_RANLIB


dnl AC_CONFIG_HEADERS([src/config.h])

AC_PROG_INSTALL

echo ""
echo " CFLAGS = $CFLAGS"
echo "LDFLAGS = $LDFLAGS"
echo ""

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	tests/Makefile
])

AC_OUTPUT
