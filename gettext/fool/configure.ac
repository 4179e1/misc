#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([fool], [0.0.1], [4179e1@gmail.com])
AC_CONFIG_SRCDIR([src/fool.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_GNU_GETTEXT_VERSION([0.17])
AM_GNU_GETTEXT([external])
AM_INIT_AUTOMAKE([gnu -Wall -Werror])


# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_LANG([C])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_OUTPUT
