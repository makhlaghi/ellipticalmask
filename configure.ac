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
AC_CHECK_HEADERS([stdlib.h string.h unistd.h argp.h], [],
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
AC_MSG_CHECKING([for date of configuration])
AC_DEFINE_UNQUOTED([CONFIGDATE], ["`date +"%d %B %Y"`"], 
                   [Date of configuration])
AC_DEFINE_UNQUOTED([CONFIGTIME], ["`date +"%H:%M"`"], 
                   [Time of configuration])
AC_MSG_RESULT([done])	

#Check if `defaults.ac` exists:
AC_MSG_CHECKING([if \`defaults.ac\` exists])
if [[ -f "$srcdir/defaults.ac" ]]; then
  source $srcdir/defaults.ac
else
  printf "\n$srcdir/defaults.ac does not exist!"; exit 1; fi
AC_MSG_RESULT([done])

#Function to check if input is a number:
checkifnumber()
{
  if ! [[[ $1 =~ ^-?[0-9]+([.][0-9]+)?$ ]]] ; then
    printf "\n\n\"$1\" in \'defaults.ac\` is not a number.\n"
    printf "Note: Replace numbers written like \".1\" with \"0.1\".\n\n"
    exit 1
  fi
}

#Read the rest of the default values and check them:
AC_MSG_CHECKING([default values in \`defaults.ac\`])

AC_DEFINE_UNQUOTED([DP_MASKNAME], ["$maskname"], [Default parameter])

if [[ -n "$naxis0" ]]; then
  checkifnumber	$naxis0
  if [[ `echo "$naxis0>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_NAXIS0_T], ["$naxis0"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_NAXIS0_V], [$naxis0], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, imgext must be >=0.\n\n"; exit 1; fi
else printf "\n\nimgext not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$naxis1" ]]; then
  checkifnumber	$naxis1
  if [[ `echo "$naxis1>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_NAXIS1_T], ["$naxis1"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_NAXIS1_V], [$naxis1], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, naxis1 must be >=0.\n\n"; exit 1; fi
else printf "\n\nnaxis1 not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$imgext" ]]; then
  checkifnumber	$imgext
  if [[ `echo "$imgext>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_IMGEXT_T], ["$imgext"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_IMGEXT_V], [$imgext], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, imgext must be >=0.\n\n"; exit 1; fi
else printf "\n\nimgext not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$xcol" ]]; then
  checkifnumber	$xcol
  if [[ `echo "$xcol>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_XCOL_T], ["$xcol"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_XCOL_V], [$xcol], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, xcol must be >=0.\n\n"; exit 1; fi
else printf "\n\nxcol not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$ycol" ]]; then
  checkifnumber	$ycol
  if [[ `echo "$ycol>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_YCOL_T], ["$ycol"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_YCOL_V], [$ycol], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, ycol must be >=0.\n\n"; exit 1; fi
else printf "\n\nycol not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$pacol" ]]; then
  checkifnumber	$pacol
  if [[ `echo "$pacol>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_PACOL_T], ["$pacol"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_PACOL_V], [$pacol], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, pacol must be >=0.\n\n"; exit 1; fi
else printf "\n\npacol not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$mjcol" ]]; then
  checkifnumber	$mjcol
  if [[ `echo "$mjcol>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_MJCOL_T], ["$mjcol"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_MJCOL_V], [$mjcol], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, mjcol must be >=0.\n\n"; exit 1; fi
else printf "\n\nmjcol not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$micol" ]]; then
  checkifnumber	$micol
  if [[ `echo "$micol>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_MICOL_T], ["$micol"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_MICOL_V], [$micol], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, micol must be >=0.\n\n"; exit 1; fi
else printf "\n\nmicol not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$multipcol" ]]; then
  checkifnumber	$multipcol
  if [[ `echo "$multipcol>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_MULTIPCOL_T], ["$xcol"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_MULTIPCOL_V], [$xcol], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, multipcol must be >=0.\n\n"; exit 1; fi
else printf "\n\nmultipcol not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

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
