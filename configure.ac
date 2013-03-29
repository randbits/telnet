#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([My Telnet Client and Server], [0.1], [])
AC_CONFIG_SRCDIR([src/client/main.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

LT_INIT

# Checks for programs.
AC_PROG_CC

AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([netdb.h stdlib.h string.h sys/socket.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset socket])

AC_CONFIG_FILES([
Makefile
docs/Makefile
lib/Makefile
src/Makefile
src/client/Makefile
src/server/Makefile
tests/Makefile
])
AC_OUTPUT
