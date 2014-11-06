# Process this file with autoconf to produce a configure script.
#
# Hand written file: used as input into GNU Autotools (autoconf).
#
# This is the autoconf instructions to build
# EllipticalMask. EllipticalMask will read elliptical parameters from
# a catalog and mask those pixels. It is free software released under
# GNU GPLv3+.
#
# Copyright (C) 2014 Mohammad Akhlaghi
# Tohoku University Astronomical Institute, Sendai, Japan.
# http://astr.tohoku.ac.jp/~akhlaghi/



# Definitions:
AC_PREREQ([2.69]) 
AC_INIT([EllipticalMask], [0.2], [makhlaghi@gmail.com], 
        [ellipticalmask], [https://github.com/makhlaghi/ellipticalmask])
AM_INIT_AUTOMAKE([-Wall -Werror foreign]) 
AC_CONFIG_SRCDIR([src/ui.h])
AC_CONFIG_HEADERS([config.h])


# Checks for programs.
${CFLAGS=""}
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([cfitsio], [main], [], [AC_MSG_ERROR([Cannot continue.])])
AC_CHECK_LIB([m], [main], [], [AC_MSG_ERROR([Cannot continue.])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h], [],
                 [AC_MSG_ERROR([Cannot continue.])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([sqrt strtol])

#Tell configure which files to work on:
AC_CONFIG_FILES([Makefile
                 src/Makefile])

#Read the configuration date.
AC_MSG_CHECKING([for date of compilation])
AC_DEFINE_UNQUOTED([CONFIGDATE], ["`date +"%d %B %Y"`"], 
                   [Date of compilation])
AC_DEFINE_UNQUOTED([CONFIGTIME], ["`date +"%H:%M"`"], 
                   [Time of compilation])
AC_MSG_RESULT([done])	

#Read the default values from defaults.sh:
source $srcdir/defaults.ac

#Read the rest of the default values:
AC_MSG_CHECKING([defaults from `default.ac`])
AC_DEFINE_UNQUOTED([DP_NAXIS0_T], ["$naxis0"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_NAXIS0_V], [$naxis0], [Default parameter])
AC_DEFINE_UNQUOTED([DP_NAXIS1_T], ["$naxis1"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_NAXIS1_V], [$naxis1], [Default parameter])
AC_DEFINE_UNQUOTED([DP_IMGEXT_T], ["$imgext"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_IMGEXT_V], [$imgext], [Default parameter])
AC_DEFINE_UNQUOTED([DP_MASKNAME], ["$maskname"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_XCOL_T], ["$xcol"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_XCOL_V], [$xcol], [Default parameter])
AC_DEFINE_UNQUOTED([DP_YCOL_T], ["$ycol"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_YCOL_V], [$ycol], [Default parameter])
AC_DEFINE_UNQUOTED([DP_PACOL_T], ["$pacol"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_PACOL_V], [$pacol], [Default parameter])
AC_DEFINE_UNQUOTED([DP_MJCOL_T], ["$mjcol"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_MJCOL_V], [$mjcol], [Default parameter])
AC_DEFINE_UNQUOTED([DP_MICOL_T], ["$micol"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_MICOL_V], [$micol], [Default parameter])
AC_DEFINE_UNQUOTED([DP_MULTIPCOL_T], ["$multipcol"], [Default parameter])
AC_DEFINE_UNQUOTED([DP_MULTIPCOL_V], [$multipcol], [Default parameter])
AC_MSG_RESULT([done])

#Make the outputs:
AC_OUTPUT
 
#Print a bye-bye message:
echo
echo "==================================================="
echo "AC_PACKAGE_STRING is now configured:"
echo
echo "You are now ready to compile AC_PACKAGE_STRING".
echo "Simply run the commands: \`make\` then \`make install\`"
echo "==================================================="
echo
