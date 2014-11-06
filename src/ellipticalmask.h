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

struct uiparams
{
  char      *imgname;	       /* Input FITS image name.              */
  char      *catname;	       /* Input ASCII table.                  */
  int         imgext;	       /* Extention of input FITS image.      */
  size_t      cat_s1;	       /* Number of columns in input table.   */
  double        *cat;	       /* Input table read into an array.     */
  int         multip;	       /* ==1: there is a multip column.      */
  size_t        xcol;	       /* Input ellipse X (FITS) col.         */
  size_t        ycol;	       /* Input ellipse Y (FITS) col.         */
  size_t       pacol;	       /* Input ellipse Position angle col.   */
  size_t       mjcol;	       /* Input ellipse Major axis col.       */
  size_t       micol;          /* Input ellipse Minor axis col.       */
  size_t   multipcol;	       /* Multiplication factor to a and b.   */
  int   tmpblankmask;	       /* Temporary value for blankmask.      */
};


struct elmaskparams
{
  struct uiparams up;	        /* Input related parameters.           */
  int           verb;		/* ==1: verbose mode.                  */
  int      blankmask;		/* Only make a blank mask.             */
  int     onlycircum;		/* 1: Only border of ellipse is shown. */
  float         *img;		/* Float array of image.               */
  size_t          s0;		/* Image zeroth axis (in C).           */
  size_t          s1;		/* Image first axis (in C).            */
  double    *intable;	        /* Table keeping the paramter values.  */
  size_t    numellip;		/* Number of rows in that table        */
  char     *maskname;		/* Output fits name.                   */
};

void
ellipmask(struct elmaskparams *p);

#endif
