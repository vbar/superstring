#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([superstring], [0.01], [vbar@comp.cz])
AC_CONFIG_SRCDIR([superstring.cc])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE(superstring, 0.01)

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([stree], [lst_alg_longest_common_substring],, [echo "libstree is required." && exit 1])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
