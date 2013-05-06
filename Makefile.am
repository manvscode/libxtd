SUBDIRS = src tests


Android.mk: Makefile.am
	@androgenizer -:PROJECT libutility \
	-:REL_TOP $(top_srcdir) -:ABS_TOP $(abs_top_srcdir) \
	-:SHARED libutility \
	-:SOURCES \
		src/bytes.c \
		src/caesar.c \
		src/checksums.c \
		src/console.c \
		src/crash.c \
		src/endianess.c \
		src/exceptions.c \
		src/fileio.c \
		src/fsm.c \
		src/huffman.c \
		src/mime.c \
	-:CFLAGS -std=c99 -Wall -O3 -I./src/ -I/usr/local/include/ -L. \
	-:LDFLAGS -ldl -lm -lcollections \
	> $@

android: Android.mk
	ndk-build NDK_PROJECT_PATH=. NDK_MODULE_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_OUT=./lib

android-clean:
	@ndk-build clean NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_OUT=./lib
