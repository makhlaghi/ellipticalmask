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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stats.h"


/****************************************************************
 *****************            Sum            ********************
 ****************************************************************/
float 
floatsum(float *in, size_t size)
{
  float *pt, *fpt;
  double sum=0;
  fpt=in+size;
  pt=in;
  while(pt<fpt) 
    sum+=*pt++;
  return sum;
}





float 
floatsumsquared(float *in, size_t size)
{
  float *pt, *fpt;
  double sum=0;
  fpt=in+size;
  for(pt=in;pt<fpt;pt++) 
    sum+=*pt * *pt;
  return sum;
}





/* Sum over all elements of the array that are not covered by a
   mask. Any non-zero masked pixel is considered to be a masked
   pixel. */
float 
floatsummask(float *in, unsigned char *mask, 
	     size_t size, size_t *nsize)
{
  double sum=0;
  float *pt, *fpt;
  size_t counter=0;
  fpt=in+size;
    
  for(pt=in;pt<fpt;pt++) 
    if(mask[pt-in]==0)
      {
	sum+=*pt;
	counter++;
      }

  *nsize=counter;
  return sum;
}





float 
floatsumsquaredmask(float *in, unsigned char *mask, 
                    size_t size, size_t *nsize)
{
  size_t counter=0;
  float *pt, *fpt;
  double sum=0;
  fpt=in+size;
  pt=in;
  for(pt=in;pt<fpt;pt++)
    if(mask[pt-in]==0)
      { 
	sum+=*pt * *pt;
	counter++;
      }
  *nsize=counter;
  return sum;
}




















/****************************************************************
 *****************      Average and STD      ********************
 ****************************************************************/
/* Find the average and standard deviation of an array, assuming that
   there is a mask array. Any mask array pixel that is not zero will
   not be included in the average and standard deviations.  Here the
   mask is assumed to be unsigned char.  */
void
favestd(float *in, size_t size, float *ave, float *std, 
	size_t *unmaskedsize, unsigned char *mask)
{
  size_t nsize1, nsize2;
  float sum, sum2;
  if(mask==NULL)
    {
      sum=floatsum(in, size);
      sum2=floatsumsquared(in, size);
    }
  else 
    {
      sum=floatsummask(in, mask, size, &nsize1);
      sum2=floatsumsquaredmask(in, mask, size, &nsize2);
      assert(nsize1==nsize2);
      size=nsize1;
    }
  *ave=sum/size;
  *std=sqrt( (sum2-sum*sum/size)/size );
  *unmaskedsize=size;
}




















/****************************************************************
 *****************           Minimum         ********************
 ****************************************************************/
void
floatmin(float *in, size_t size, float *min)
{
  float tmin=MAXFD, *fpt;
  fpt=in+size;
  do
    if(*in<tmin) tmin=*in;
  while (++in<fpt);
  *min=tmin;
}
