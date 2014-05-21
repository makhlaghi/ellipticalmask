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

#include "sll.h"
#include "pix.h"
#include "stats.h"
#include "raddist.h"
#include "arraymanip.h"
#include "fitsarrayvv.h"
#include "ellipticalmask.h"




/* Find the first pixel in the image to begin building the profile.

   The input sizes and positions are based on the FITS standard,
   But in main(), we reversed the sizes to fits the C standard and
   when calling this function, we reversed the positions to fit
   the C standard. So by the time they get here, the inputs are
   all in the C standard.*/
void
findstartingpixel(size_t s0, size_t s1, float truncr, 
		  struct elraddistp *e, size_t *p)
{
  float rmin, x_c, y_c, fs0, fs1;
  int is0, is1, i, j, x, y, x1, y1, x2, y2;
  size_t x_w, y_w, xmin=NONINDEX, ymin=NONINDEX;

  is0=s0; is1=s1;
  x_c=e->xc; y_c=e->yc;

  /* Find the central pixel, this will be needed if it is inside the
     image or outside it. */
  if(x_c-(int)x_c>0.5) x=x_c+1;
  else x=x_c;
  if(y_c-(int)y_c>0.5) y=y_c+1;
  else y=y_c;

  /* The central pixel is in the image, set the pixel and return. */
  fs0=s0;/* Just to make things easier! */
  fs1=s1;
  if(x_c>=0 && x_c<fs0 && y_c>=0 && y_c<fs1)
    {
      *p=x*s1+y;
      return;
    }

  /* The center is out of the image. Use encloseellipse() from
   raddist.c to see if any of the pixels within the truncation
   radius fit into the image.*/
  encloseellipse(truncr, e->q*truncr, e->t, &x_w, &y_w);
  x1=x-x_w/2;
  y1=y-y_w/2;
  x2=x+x_w/2;
  y2=y+y_w/2;
  
  /* Check if any of the four corners of the box inclosing the
     profile are in the mock image. If they are not, x1=x2 or
     y1=y2*/
  checkifinarray(&x1, &y1, &x2, &y2, s0, s1);
  if(x1==x2 || y1==y2)    
    {     /* The profile's region is */
      *p=NONINDEX;     /* Completely out of the image. */
      return;     /* Return NULL. */
    }
  else     /* The profile and the image overlap */
    {     /* Find the point on the side of the */
      rmin=1e10;     /* image with the smallest radius. */
      if(x1==0)     /* This is important, because the  */
	for(j=y1;j<y2;j++)   /* first check later will be  */
	  if(elraddist(e, 0, j)<rmin)
	    {     /* integration and we want to be sure  */
              xmin=0; ymin=j; /* we start with the smallest radius. */
	      rmin=elraddist(e, 0, j); /* in the image. */
	    }
      if(x2==is0)       
	for(j=y1;j<y2;j++)
	  if(elraddist(e, s0-1, j)<rmin)
	    {
              xmin=s0-1; ymin=j;
	      rmin=elraddist(e, s0-1, j);
	    }
      if(y1==0)       
	for(i=x1;i<x2;i++)
	  if(elraddist(e, i, 0)<rmin)
	    {
              xmin=i; ymin=0;
	      rmin=elraddist(e, i, 0);
	    }
      if(y2==is1)       
	for(i=x1;i<x2;i++)
	  if(elraddist(e, i, s1-1)<rmin)
	    {
              xmin=i; ymin=s1-1;
	      rmin=elraddist(e, i, s1-1);
	    }
      if(rmin<truncr && xmin!=NONINDEX && ymin!=NONINDEX)
	*p=xmin*s1+ymin;
      else *p=NONINDEX;
    }
}





/* See MockGals's ( http://astr.tohoku.ac.jp/~akhlaghi/mockgals )
   makeprofile() in src/mock.c and documentation for a very detailed
   review of how this function works.*/
int
makemask(unsigned char *mask, size_t *ngbs, size_t s0, size_t s1, 
	 float x_c, float y_c, float pa_d, float q, float truncr)
{
  float r;
  size_t ngbi, p;
  struct elraddistp e;
  struct ssll *Q=NULL;
  
  e.q=q;
  e.t=M_PI*pa_d/180;
  e.xc=x_c;          e.yc=y_c;
  e.cos=cos(e.t);    e.sin=sin(e.t);

  findstartingpixel(s0, s1, truncr, &e, &p);
  if(p==NONINDEX)
    return 0;

  add_to_ssll(&Q, p);  

  while(Q)
    {
      pop_from_ssll(&Q, &p);

      r=elraddist(&e, p/s1, p%s1);
      if(r>truncr) continue;
      
      mask[p]=1; 

      /*array_to_fits("tmp2.fits", NULL, "", FLOAT_IMG, img, s0, s1);*/

      /* 4-connected neighbors are enough. */
      ngbi=p*NGBSCOLS+ngbs[p*NGBSCOLS];
      do
	if(mask[ p=ngbs[ngbi] ]==0)
	  add_to_ssll(&Q, p);
      while(ngbs[++ngbi]!=NONINDEX);
    }

  return 1;
}




void
ellipmask(struct elmaskparams *p)
{
  double *t;
  unsigned char *mask;
  size_t i, nc, size, *ngbs;
  float sky, skystd, maskvalue;

  size=p->s0*p->s1;
  assert( ( mask=calloc(size, sizeof *mask) )!=NULL  );
  imgngbs(p->s0, p->s1, &ngbs);

  t=p->intable;
  nc=ELTABLENUMCOLS;

  for(i=0;i<p->numellip;i++)
    makemask(mask, ngbs, p->s0, p->s1, t[i*nc+XCOL], t[i*nc+YCOL],
	     90-t[i*nc+PACOL], t[i*nc+QCOL], t[i*nc+TRUNCCOL]);
  
  if(p->blankmask)
    array_to_fits(p->outname, NULL, "MASKED", BYTE_IMG, mask, 
		  p->s0, p->s1);
  else
    {
      if(p->reportsky)
	{
	  favestd(p->img, size, &sky, &skystd, mask);
	  printf("\nUndetected regions: average: %f, std: %f\n", 
		 sky, skystd);
	}
      floatmin(p->img, size, &maskvalue);
      maskvalue-=1;
      maskfloat(p->img, mask, size, maskvalue);
      array_to_fits(p->outname, NULL, "MASKED", FLOAT_IMG, p->img, 
		    p->s0, p->s1);
    }

  free(ngbs);
  free(mask);
}
