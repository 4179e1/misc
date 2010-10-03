#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.65)
AC_INIT([librio],[0.0.1],[4179e1@gmail.com])
AC_CONFIG_SRCDIR([src/librio.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([gnu -Wall -Werror])
LT_INIT

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
