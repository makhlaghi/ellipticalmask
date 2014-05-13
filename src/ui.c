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
#include "attaavv.h"
#include "fitsarrayvv.h"
#include "ellipticalmask.h"

#include "ui.h"			/* Needs ellipticalmask.h */





/****************************************************************
 *****************     Small functions used    ******************
 *********************      in main()      **********************
 ****************************************************************/
/* Set the default values for the inputs. */
void
setdefaultoptions(struct elmaskparams *p, struct uiparams *up)
{
  /* Options for ellipticalmask.c */
  p->verb          = 0;
  p->img           = NULL;
  p->intable       = NULL;
  p->numellip      = 0;
  p->outname       = "masked.fits";
  p->s0            = 200;
  p->s1            = 200;

  /* Internal options for ui.c */
  up->intablename   = "";
  up->infitsname    = "";
  up->x_col         = 2;
  up->y_col         = 3;
  up->pa_col        = 4;
  up->a_col         = 5;
  up->b_col         = 6;
  up->multip_col    = 7;
  up->onlyimagesize = 0;
}





/* If the input table exists, read it and put its pointer into the
   input structure. If it doesn't exist, then raise an error and
   abort */
void
readinputinfo(struct elmaskparams *p, struct uiparams *up)
{
  int abort=0;
  FILE *tmpfile;
  struct ArrayInfo intable;

  if ((tmpfile = fopen(up->intablename, "r")) != NULL) 
    {
      fclose(tmpfile);
      readasciitable(up->intablename, &intable);

      /* Check the columns to see if they are all inside the width. */
      if(up->x_col>=intable.s1)
	{printf("X column(%lu) larger than number of columns (%lu)\n",
		up->x_col+1, intable.s1); abort=1;}
      if(up->y_col>=intable.s1)
	{printf("Y column(%lu) larger than number of columns (%lu)\n",
		up->y_col+1, intable.s1); abort=1;}
      if(up->pa_col>=intable.s1)
	{printf("PA column(%lu) larger than number of columns (%lu)\n",
		up->pa_col+1, intable.s1); abort=1;}
      if(up->a_col>=intable.s1)
	{printf("A column (%lu) larger than number of columns (%lu)\n",
		up->a_col+1, intable.s1); abort=1;}
      if(up->b_col>=intable.s1)
	{printf("B column (%lu) larger than number of columns (%lu)\n",
		up->b_col+1, intable.s1); abort=1;}
      if(up->multip_col>=intable.s1)
	{printf("M column (%lu) larger than number of columns (%lu)\n",
		up->multip_col+1, intable.s1); abort=1;}
      if(abort)	  exit(EXIT_FAILURE);

      p->numellip=intable.s0;
      up->intable_s1=intable.s1;

      up->intable=intable.d;
      intable.d=malloc(sizeof *(intable.d));/*freeasciitable() has */
      assert(intable.d!=NULL);		    /*something to free!   */

      freeasciitable(&intable);
      if(p->verb)
	printf("- Information for %lu ellipse%sread from '%s'.\n\n",
	     p->numellip, p->numellip>1 ? "s " : " ", up->intablename);
    }
  else 
    {
      fprintf(stderr, "\n\n\tERROR: Can't read %s.\n",up->intablename);
      fprintf(stderr, "\t\tAborted\n\n");
      exit(EXIT_FAILURE);
    }
}





void
makeelparamstable(struct elmaskparams *p, struct uiparams *up)
{
  double *itable, *ftable;
  size_t i, numrows, icols;
  size_t x_col, y_col, pa_col, a_col, b_col, multip_col;

  itable=up->intable;
  ftable=malloc(ELTABLENUMCOLS*p->numellip*sizeof *ftable);
  assert(ftable!=NULL);

  /* To make things clean in the loop and convert to counting from
     zero. */
  numrows=p->numellip;           icols=up->intable_s1;
  x_col=up->x_col-1;             y_col=up->y_col-1;      
  a_col=up->a_col-1;             b_col=up->b_col-1;
  multip_col=up->multip_col-1;   pa_col=up->pa_col-1;

  for(i=0;i<numrows;i++)
    {
      ftable[i*ELTABLENUMCOLS+XCOL]=itable[i*icols+y_col]-1;
      ftable[i*ELTABLENUMCOLS+YCOL]=itable[i*icols+x_col]-1;
      ftable[i*ELTABLENUMCOLS+PACOL]=itable[i*icols+pa_col];
      ftable[i*ELTABLENUMCOLS+QCOL]=
	itable[i*icols+b_col]/itable[i*icols+a_col];
      ftable[i*ELTABLENUMCOLS+TRUNCCOL]=
	itable[i*icols+a_col]*itable[i*icols+multip_col];
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





#define MAXFD 1e30
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





void
readmakeinputimage(struct elmaskparams *p, struct uiparams *up)
{
  void *img;
  int bitpix;
  FILE *tmpfile;
  
  if ((tmpfile = fopen(up->infitsname, "r")) != NULL) 
    {
      fclose(tmpfile);
      fits_to_array(up->infitsname, 0, &bitpix, &img, &p->s0, &p->s1);
      if(up->onlyimagesize)
	{
	  free(img);  	/* Free the array fits_to_array allocated */
	  img=calloc(p->s0*p->s1, sizeof(float));
	  assert(img!=NULL);
	  p->maskvalue=1;
	}
      else
	{
	  if(bitpix!=FLOAT_IMG)
	    {
	      printf("\n\nError: Only Float image is valid\n\n");
	      exit(EXIT_FAILURE);
	    }
	  floatmin(img, p->s0*p->s1, &p->maskvalue);
	  p->maskvalue-=1;
	}
    }
  else
    {
      img=calloc(p->s0*p->s1, sizeof(float));
      assert(img!=NULL);
      p->maskvalue=1;
    }

  p->img=img;
}



















/****************************************************************
 *****************        Read options:      ********************
 ****************************************************************/
/* Check if the two size paramters are positive. */
void
checksize(char *optarg, size_t *var, int opt)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(tmp<=0)
    {
      printf("\n\n Error: argument to -%c ", opt); 
      printf("should be positive\n\n");
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
printversioninfo()
{
  printf("\n\nEllipticalMask %.1f\n", ELMASKVERSION);
  printf("============\n");
  printf("Make any number of elliptical masks on an image.\n");
  printf("\nCopyright (C) 2014  Mohammad Akhlaghi\n");
  printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
  printf("This is free software, and you are welcome to\n");
  printf("modify and redistribute it under the\n");
  printf("GNU Public License v3 or later.\n\n\n");
}




/* Print the help menu. */
void
printhelp(struct elmaskparams *p, struct uiparams *up)
{
  printversioninfo();

  printf("\n\n###### Options that won't run EllipticalMask\n");
  printf(" -h:\n\tPrint this help message.\n\n");
  printf(" -v:\n\tPrint version and copyright information.\n\n\n");

  printf("\n\n###### Options with no arguments:\n");
  printf(" -z:\n\tOnly use the image size, mask an empty image\n\n");

  printf("\n\n###### Options with arguments:\n");
  printf(" -x INTEGER:\n\tThe NAXIS0 size of the ");
  printf("output FITS image.\n");
  printf("\tIf -I (input FITS) is given, this is ignored.\n");
  printf("\tdefault: %lu pixels\n\n", p->s1);

  printf(" -y INTEGER:\n\tThe NAXIS1 size of the ");
  printf("output FITS image.\n");
  printf("\tIf -I (input FITS) is given, this is ignored.\n");
  printf("\tdefault: %lu pixels\n\n", p->s0);

  printf(" -i FILENAME:\n\tInput ASCII table.\n");
  printf("\tNo default. Must be provided.\n\n");

  printf(" -I FILENAME:\n\tInput FITS name.\n");
  printf("\tIf not provided, a blank (all zero) image is made.\n\n");

  printf(" -o FILENAME:\n\tOutput FITS image name.\n");
  printf("\tdefault: '%s'\n\n", p->outname);

  printf("\n\n----- Input table column info (count from one):\n");
  printf(" -a INTEGER:\n\tX position (FITS standard) column.\n");
  printf("\tdefault: '%lu'\n\n", up->x_col);

  printf(" -b INTEGER:\n\tY position (FITS standard) column.\n");
  printf("\tdefault: '%lu'\n\n", up->y_col);

  printf(" -c INTEGER:\n\tPosition angle (in degrees) column.\n");
  printf("\tdefault: '%lu'\n\n", up->pa_col);

  printf(" -d INTEGER:\n\tMajor axis column.\n");
  printf("\tdefault: '%lu'\n\n", up->a_col);

  printf(" -e INTEGER:\n\tMinor axis column column.\n");
  printf("\tdefault: '%lu'\n\n", up->b_col);

  printf(" -f INTEGER:\n\tMajor axis multiple column.\n");
  printf("\tdefault: '%lu'\n\n", up->multip_col);

  exit(0);
}





/* Read all the options into the program */
void
getsaveoptions(struct elmaskparams *p, int argc, char *argv[])
{
  int c;
  char *tailptr; 
  struct uiparams up;

  setdefaultoptions(p, &up);

  while( (c=getopt(argc, argv, "vhzx:y:i:I:a:b:c:d:e:f:")) 
	 != -1 )
    switch(c)
      {
	/* Options with no arguments: */
      case 'v':			/* Print version and copyright. */
	printversioninfo();
	exit(EXIT_FAILURE);
      case 'h':			/* Print help. */
	printhelp(p, &up);
	exit(EXIT_FAILURE);
      case 'z':			/* Print help. */
	up.onlyimagesize=1;
	break;

	/* Options with argument: */
      case 'x':			/* NAXIS1 value of output image. */
	checksize(optarg, &p->s1, c);
	break;
      case 'y':			/* NAXIS2 value of output image. */
	checksize(optarg, &p->s0, c);
	break;
      case 'i':			/* Input table. */
	up.intablename=optarg;
	break;
      case 'I':			/* Input FITS name. */
	up.infitsname=optarg;
	break;
      case 'o': 		/* Output fits name. */
	p->outname=optarg;
	break;
      case 'a':
	up.x_col=strtol(optarg, &tailptr, 0);
	break;
      case 'b':
	up.y_col=strtol(optarg, &tailptr, 0);
	break;
      case 'c':
	up.pa_col=strtol(optarg, &tailptr, 0);
	break;
      case 'd':
	up.a_col=strtol(optarg, &tailptr, 0);
	break;
      case 'e':
	up.b_col=strtol(optarg, &tailptr, 0);
	break;
      case 'f':
	up.multip_col=strtol(optarg, &tailptr, 0);
	break;
      case '?':
	fprintf(stderr, "Unknown option: '-%c'.\n\n", optopt);
	exit(EXIT_FAILURE);
      default:
	abort();
      }
  
  /* Read the input table specifying the elliptical parameters. */
  readinputinfo(p, &up);
  makeelparamstable(p, &up);
  checkremoveoutimage(p->outname);
  readmakeinputimage(p, &up);

  free(up.intable);
}
