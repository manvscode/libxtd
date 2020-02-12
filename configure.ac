AC_PREREQ(2.67)
AC_INIT([libutility], [1.0], [manvscode@gmail.com], [libutility], [http://www.manvscode.com/])
AM_INIT_AUTOMAKE([1.13 foreign silent-rules -Wall -Werror])

AC_CONFIG_MACRO_DIR([m4])

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

# AC_CANONICAL_HOST is needed to access the 'host_os' variable
AC_CANONICAL_HOST

build_linux=no
build_windows=no
build_mac=no

# Detect the target system
case "${host_os}" in
    linux*)
        build_linux=yes
        ;;
    cygwin*|mingw*)
        build_windows=yes
        ;;
    darwin*)
        build_mac=yes
        ;;
    *)
        AC_MSG_ERROR(["OS $host_os is not supported"])
        ;;
esac

# Pass the conditionals to automake
AM_CONDITIONAL([LINUX], [test "$build_linux" = "yes"])
AM_CONDITIONAL([WINDOWS], [test "$build_windows" = "yes"])
AM_CONDITIONAL([OSX], [test "$build_mac" = "yes"])


#CFLAGS="-std=c11 -Wall -pedantic -fsanitize=undefined -g -ggdb -O0 -DDEBUG -I/usr/local/include/"
CFLAGS="$CFLAGS"
LDFLAGS="$LDFLAGS"

AM_PROG_AR


LT_INIT([shared static win32-dll])

AS_IF([test "$build_linux" = "yes"], [
	AC_MSG_NOTICE([Building for Linux.])
],[test "$build_windows" = "yes"],[
	AC_MSG_NOTICE([Building for Microsoft Windows.])
	LDFLAGS="$LDFLAGS -no-undefined"
],[
	AC_MSG_NOTICE([Building for MacOS X.])
])


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
