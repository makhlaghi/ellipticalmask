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
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "config.h"
#include "attaavv.h"
#include "fitsarrayvv.h"
#include "ellipticalmask.h"

#include "ui.h"			/* Needs ellipticalmask.h */
#include "argpparser.h"         /* Needs ellipticalmask.h */










/****************************************************************
 ***************        Prepare parameters        ***************
 ****************************************************************/
void
intelzero(char *optarg, int *var, char *lo, char so)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(strlen(tailptr))
    {
      fprintf(stderr, PACKAGE": the argument to option `-%c`: `%s` was not "
	     "readable as a number!\n", so, optarg);
      exit(EXIT_FAILURE);
    }
  if(tmp<0)
    {
      fprintf(stderr, PACKAGE": argument to `--%s (-%c)` should be >=0, "
	     "it is: %ld\n", lo, so, tmp);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
sizetelzero(char *optarg, size_t *var, char *lo, char so)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(strlen(tailptr))
    {
      fprintf(stderr, PACKAGE": the argument to option `-%c`: `%s` was not "
	     "readable as a number!\n", so, optarg);
      exit(EXIT_FAILURE);
    }
  if(tmp<0)
    {
      fprintf(stderr, PACKAGE": argument to `--%s (-%c)` should be >=0, it "
	     "is: %ld\n", lo, so, tmp);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}




/* If the input table exists, read it and put its pointer into the
   input structure. If it doesn't exist, then raise an error and
   abort */
#define FIXEDSTATEMENT " larger than max column index (%lu)\n"
void
readcat(struct elmaskparams *p)
{
  int abort=0;
  FILE *tmpfile;
  struct ArrayInfo intable;
  struct uiparams *up=&p->up;

  if ((tmpfile = fopen(up->imgname, "r")) != NULL) 
    {
      /* Read the input catalog and save it in the intable structure. */
      fclose(tmpfile);
      readasciitable(up->catname, &intable);

      /* Check the column indexs to see if they all fit the catalog. */
      if(up->xcol>intable.s1-1)
	{
	  fprintf(stderr, PACKAGE": X column(%lu)"FIXEDSTATEMENT,
		 up->xcol, intable.s1-1);
	  abort=1;
	}
      if(up->ycol>=intable.s1-1)
	{
	  fprintf(stderr, PACKAGE": Y column(%lu)"FIXEDSTATEMENT,
		  up->ycol, intable.s1-1);
	  abort=1;
	}
      if(up->pacol>=intable.s1-1)
	{
	  fprintf(stderr, PACKAGE": PA column(%lu)"FIXEDSTATEMENT,
		  up->pacol, intable.s1-1);
	  abort=1;
	}
      if(up->mjcol>=intable.s1-1)
	{
	  fprintf(stderr, PACKAGE": Major axis column(%lu)"FIXEDSTATEMENT,
		  up->mjcol, intable.s1-1);
	  abort=1;
	}
      if(up->micol>=intable.s1-1)
	{
	  fprintf(stderr, PACKAGE": Minor axis column(%lu)"FIXEDSTATEMENT,
		  up->micol, intable.s1-1);
	  abort=1;
	}
      if(up->multip && up->multipcol>=intable.s1-1)
	{
	  fprintf(stderr, PACKAGE": Multiple column(%lu)"FIXEDSTATEMENT,
		  up->multipcol, intable.s1-1);
	  abort=1;
	}
      if(abort)
	exit(EXIT_FAILURE);

      /* Read the necessary information from intable: */
      up->cat=intable.d;
      up->cat_s1=intable.s1;
      p->numellip=intable.s0;

      /* Free the intable structure. I am allocating something here so
	 freeasciitable() has something to free! */
      intable.d=malloc(sizeof *(intable.d));
      assert(intable.d!=NULL);		    
      freeasciitable(&intable);
    }
  else 
    {
      fprintf(stderr, PACKAGE": Can't read input table %s.\n", 
	      up->catname);
      exit(EXIT_FAILURE);
    }
}





void
makeelparamstable(struct elmaskparams *p)
{
  int multip=p->up.multip;
  struct uiparams *up=&p->up;
  double *itable=up->cat, *ftable=NULL;
  size_t i, numrows=p->numellip, icols=up->cat_s1;
  
  ftable=malloc(ELTABLENUMCOLS*p->numellip*sizeof *ftable);
  assert(ftable!=NULL);

  for(i=0;i<numrows;i++)
    {
      ftable[i*ELTABLENUMCOLS+XCOL]=itable[i*icols+up->xcol]-1;
      ftable[i*ELTABLENUMCOLS+YCOL]=itable[i*icols+up->ycol]-1;
      ftable[i*ELTABLENUMCOLS+PACOL]=itable[i*icols+up->pacol];
      ftable[i*ELTABLENUMCOLS+QCOL]=
	itable[i*icols+up->micol]/itable[i*icols+up->mjcol];
      if(multip)
	ftable[i*ELTABLENUMCOLS+TRUNCCOL]=
	  itable[i*icols+up->mjcol]*itable[i*icols+up->multipcol];
      else
	ftable[i*ELTABLENUMCOLS+TRUNCCOL]=itable[i*icols+up->mjcol];
    }

  p->intable=ftable;
}





/* Check if the output image exists. If so, remove it. */
void
checkremoveoutimage(char *outname)
{
  FILE *tmpfile;
  if ((tmpfile = fopen(outname, "r")) != NULL) 
    {
      fclose(tmpfile);
      if(unlink(outname)==-1)
	{
	  fprintf(stderr, "'%s' already exists and could", outname); 
	  fprintf(stderr, " not be removed");
	  exit(EXIT_FAILURE);
	}
    }
}






void
readmakeinputimage(struct elmaskparams *p)
{
  void *img;
  int bitpix;
  FILE *tmpfile;
  struct uiparams *up=&p->up;

  /* Image exists and is read: */
  if(up->imgname)
    {
      if(p->s0 || p->s1)
	fprintf(stderr, PACKAGE": An input image (%s) and at least on of "
		"`--naxis0` and `--naxis1` are also specified! The image "
		"size will take precedence.\n", up->imgname);
      
      if ((tmpfile = fopen(up->imgname, "r")) != NULL) 
	{
	  fclose(tmpfile);
	  fits_to_array(up->imgname, up->imgext, &bitpix, &img,
			&p->s0, &p->s1);
	  if(up->tmpblankmask)
	    {
	      p->blankmask=1;
	      free(img);
	      img=NULL;	      
	    }
	  else
	    if(bitpix!=FLOAT_IMG)
	      {
		fprintf(stderr, PACKAGE": Currently only float image "
			"is valid\n");
		exit(EXIT_FAILURE);
	      }
	}
      else
	{
	  fprintf(stderr, PACKAGE": %s could not be opened.\n",
		  up->imgname);
	  exit(EXIT_FAILURE);
	}
    }
  /* No input image specified. */
  else 
    {
      if(p->s0==0 || p->s1==0)
	{
	  fprintf(stderr, PACKAGE": When no image is defined,\n"
		 "both size parameters (--naxis0 & --naxis1)\n" 
		 "have to be set:\n");
	  if(p->s0==0) printf("-y has not been set.\n");
	  if(p->s1==0) printf("-x has not been set.\n");
	  exit(EXIT_FAILURE);
	}
      img=NULL;
      p->blankmask=1; /* Just incase the user forgot to ask. */
    }

  p->img=img;
}



















/****************************************************************
 *************      Read the parameters:      *******************
 ****************************************************************/
/* Read all the options into the program */
void
setparams(struct elmaskparams *p, int argc, char *argv[])
{
  struct uiparams *up=&p->up;

  /* Set the default `up` parameters: */
  up->imgname       = NULL;
  up->catname       = NULL;
  up->imgext        = DP_IMGEXT_V;
  up->cat_s1        = 0;
  up->cat           = NULL;
  up->multip        = 1;
  up->xcol          = DP_YCOL_V;
  up->ycol          = DP_XCOL_V;
  up->pacol         = DP_PACOL_V;
  up->mjcol         = DP_MJCOL_V;
  up->micol         = DP_MICOL_V;
  up->multipcol     = DP_MULTIPCOL_V;
  up->tmpblankmask  = 0;
  
  /* Set the default `elmaskparams` parameters: */
  p->verb           = 1;
  p->blankmask      = 0;
  p->onlycircum     = 0;
  p->img            = NULL;
  p->s0             = DP_NAXIS1_V;
  p->s1             = DP_NAXIS0_V;
  p->intable        = NULL;
  p->numellip       = 0;
  p->maskname       = DP_MASKNAME;

  /* Read the command line parameters: */
  argp_parse(&argp, argc, argv, 0, 0, p);

  /* Do all the readings and checkings: */
  readcat(p);
  makeelparamstable(p);
  checkremoveoutimage(p->maskname);
  readmakeinputimage(p);
  free(up->cat);
}
