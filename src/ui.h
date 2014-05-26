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
#ifndef UI_H
#define UI_H

struct uiparams
{
  char *infitsname;	       /* Input FITS image name.            */
  char *intablename;	       /* Input ASCII table.                */
  size_t inexten;	       /* Extention of input FITS image.    */
  size_t intable_s1;	       /* Number of columns in input table. */
  double *intable;	       /* Input table read into an array.   */
  size_t x_col;		       /* Input ellipse X (FITS) col.       */
  size_t y_col;		       /* Input ellipse Y (FITS) col.       */
  size_t pa_col;	       /* Input ellipse Position angle col. */
  size_t a_col;		       /* Input ellipse Major axis col.     */
  size_t b_col;		       /* Input ellipse Minor axis col.     */
  size_t multip_col;	       /* Multiplication factor to a and b. */
};

void
getsaveoptions(struct elmaskparams *p, 
	       int argc, char *argv[]);

#endif
