/*********************************************************************
ellipticalmask - Mask (set to minimum image value) pixels within 
                 an ellipse.

Copyright (C) 2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

ellipticalmask is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ellipticalmask is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ellipticalmask. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#ifndef ELLIPTICALMASK_H
#define ELLIPTICALMASK_H

/* An internal array is going to keep the variables for each
   ellipse. The columns of this ellipse are defined here: */
#define ELTABLENUMCOLS 5
#define XCOL      0	       
#define YCOL      1
#define PACOL     2
#define QCOL      3
#define TRUNCCOL  4


struct elmaskparams
{
  int    blankmask;		/* Only make a blank mask. */
  int    reportsky;		/* 1: Report sky, 0: Don't. */
  int   onlycircum;		/* 1: Only border of ellipse is shown. */
  float       *img;		/* Float array of image. */
  size_t        s0;		/* Image zeroth axis (in C). */
  size_t        s1;		/* Image first axis (in C). */
  double  *intable;	        /* Table keeping the paramter values. */
  size_t  numellip;		/* Number of rows in that table */
  char    *outname;		/* Output fits name. */
  float  maskvalue;		/* Value to be used as mask. */
};

void
ellipmask(struct elmaskparams *p);

#endif
