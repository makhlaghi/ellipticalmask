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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



/* Check to see if a box defined by the two points (x1,y1) and (x2,y2)
   is inside an array of size size1 and size2. If it doesn't overlap,
   then x1=x2 and y1=y2.*/
void
checkifinarray(int *x1, int *y1, int *x2, int *y2, int s0, int s1)
{
  int temp;
  if(*x1==*x2 && *y1==*y2) return;        

  if(*x2<*x1){temp=*x1;*x1=*x2;*x2=temp;} 
  if(*y2<*y1){temp=*y1;*y1=*y2;*y2=temp;}

  if(*x1<0) *x1=0;    if(*x1>s0) *x1=s0;
  if(*y1<0) *y1=0;    if(*y1>s1) *y1=s1;
  if(*x2<0) *x2=0;    if(*x2>s0) *x2=s0;
  if(*y2<0) *y2=0;    if(*y2>s1) *y2=s1;
}





/* Mask (set all masked pixels to a desired value) a float array: */
void
maskfloat(float *in, unsigned char *mask, size_t size, float maskvalue)
{
  unsigned char *f;
  f=mask+size;

  do
    {
      if(*mask) *in=maskvalue;
      in++;
    }
  while(++mask<f);
 
}
