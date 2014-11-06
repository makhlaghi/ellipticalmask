## Process this file with automake to produce Makefile.in
##
## Hand written file: used as input into Autotools.
##
## NOTE:
## This file will be called by the Makefile.am in the top directory,
## so this file does not need to be called directly by automake to
## make the full ellipticalmask package.
##
## This is the automake instructions to build EllipticalMask.
## EllipticalMask will read elliptical parameters from a catalog and
## mask those pixels. It is free software released under GNU GPLv3+.
##
## Copyright (C) 2014 Mohammad Akhlaghi
## Tohoku University Astronomical Institute, Sendai, Japan.
## http://astr.tohoku.ac.jp/~akhlaghi/

AM_CFLAGS = -Wall -O3
##AM_CFLAGS = -Wall -g -O0
AM_LDFLAGS = -lcfitsio -lm

bin_PROGRAMS = ellipticalmask
ellipticalmask_SOURCES = main.c main.h ellipticalmask.c			\
ellipticalmask.h ui.c ui.h attaavv.c attaavv.h fitsarrayvv.c		\
fitsarrayvv.h arraymanip.c arraymanip.h raddist.c raddist.h sll.c	\
sll.h pix.c pix.h stats.c stats.h argpparser.h
