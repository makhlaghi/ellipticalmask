/*********************************************************************
ellipticalmask - Mask pixels within an ellipse from a catalog.

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
#ifndef ARGPPARSER_H
#define ARGPPARSER_H

#include <argp.h>



/* Definition parameters for the argp: */
const char *argp_program_version=PACKAGE_STRING
  "\nCopyright (C) 2014 Mohammad Akhlaghi.\n"
  "License GPLv3+: GNU GPL version 3 or later "
  "<http://gnu.org/licenses/gpl.html>\n"
  "This is free software: you are free to change "
  "and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.";





const char *argp_program_bug_address=PACKAGE_BUGREPORT;





static char args_doc[] = "ASCIIcatalog FITSimage.fits";





const char doc[] = 
  /* Before the list of options: */
  "\n" PACKAGE_STRING" -- Mask pixels within an ellipse from a catalog.\n"
  "Configured for this machine on "CONFIGDATE", "CONFIGTIME".\n\n"
  "When calling the short format of the options, simply put your input "
  "value after the short version of the option, an equal sign (=) should "
  "not be used. For example, `-e4` or `-e 4` are the same as calling "
  "`--imgext=4`.\n\n"
  "The three capital letters after the long options indicate that providing "
  "a value is mandatory if the option is called. The letters show the "
  "format your input will be stored in:\n"
  "   INT:  An integer.\n"
  "   STR:  A string of characters (for example a file name).\n\n"
  "The default values for options are shown in the `[...]` immediately "
  "before the description for that option. Defaults are set and can be "
  "changed before running `./configure` in the `defaults.ac` file."
  /* After the list of options: */
  "\v"
  PACKAGE_NAME" home page: "PACKAGE_URL;





/* The options are classified into these categories:
   1. Operating mode like quiet, help and version.
   2. Input (image, mask and kernel name, extensions and ...)
   3. Meshs and threads.
   4. Detection 

   Available letters for short options:
   c d f g h k l o s t v w z
   A C D E F G H I J K L M N O P Q R S T U W X Y Z

   Number keys used: <=500.

   Options with keys (second structure element) larger than 500 do not
   have a short version.
 */
static struct argp_option options[] =
  {
    /* Such cases are group headers */
    {
      0, 0, 0, 0,  		/* These have to be zero for groups. */
      "Operating modes:", 	/* Explanation for the group. */
      -1			/* Group ID. */
    },
    {
      "quiet",		      /* Long name for this option.         */
      'q',		      /* Short name or key for this option. */
      0,		      /* Informative type of value it gets. */
      0,                      /* Flags for this option. */
      "By default all the steps are reported. If this option is called, "
      "only errors or warnings will be reported.\n",
      -1		      /* Option group ID. */
    },
    {
      "onlycircum",
      'r',
      0,
      0,
      "By default the full area of the ellipse is masked. If this option "
      "is called, only the circumference of the ellipse is shown.\n",
      -1
    },
    {
      "blankmask",
      'B',
      0,
      0,
      "If an input image is specified, the mask will be put in the "
      "image. If this option is called, only the sizes of the input "
      "image will be used and the mask will be put on a blank image.\n",
      -1      
    },





    {
      0, 0, 0, 0,  		/* These have to be zero for groups. */
      "Inputs:",		/* Explanation for the group. */
      1				/* Group ID. */
    },
    {
      "imgext", 		
      'e', 		
      "INT",
      0,
      "["DP_IMGEXT_T"] The input image fits extension number, starting "
      "from 0 (zero).\n",
      1
    },
    {
      "naxis0", 		
      'a', 		
      "INT",
      0,
      "["DP_NAXIS0_T"] If no image is input, number of pixels on the "
      "first fits axis of the output mask (horizontal in SAO ds9).\n",
      1
    },
    {
      "naxis1", 		
      'b', 		
      "INT",
      0,
      "["DP_NAXIS0_T"] If no image is input, number of pixels on the "
      "second fits axis of the output mask (vertical in SAO ds9).\n",
      1
    },
    {
      "maskname",
      'm', 		
      "STR",
      0,
      "["DP_MASKNAME"] The name of the FITS file that the mask will be "
      "saved in.\n",
      1
    },    
    






    {
      0, 0, 0, 0,  
      "Catalog columns, counting from 0 (zero):",
      2
    },
    {
      "xcol",
      'x', 		
      "INT",
      0,
      "["DP_XCOL_T"] First fits axis column number in catalog.\n",
      2
    },
    {
      "ycol",
      'y', 		
      "INT",
      0,
      "["DP_YCOL_T"] Second fits axis column number in catalog.\n",
      2
    },
    {
      "pacol",
      'p', 		
      "INT",
      0,
      "["DP_PACOL_T"] Position angle column number in catalog.\n",
      2
    },
    {
      "mjcol",
      'j', 		
      "INT",
      0,
      "["DP_MJCOL_T"] Major axis column number in catalog.\n",
      2
    },
    {
      "micol",
      'i', 		
      "INT",
      0,
      "["DP_MICOL_T"] Minor axis column number in catalog.\n",
      2
    },
    {
      "nomultip",
      'n',
      0,
      0,
      "By default it is assumed that one column contains a multiple for "
      "the major and minor axises. If this option is called, no multiples "
      "will be assumed.\n",
      2      
    },
    {
      "multipcol",
      'u', 		
      "INT",
      0,
      "["DP_MULTIPCOL_T"] Column showing multiple column number in catalog. "
      "Will not be used if `--nomultip` is called.\n",
      2
    },



    

    {0}
  };





/* Parse a single option: */
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
  /* Save the arguments structure: */
  struct elmaskparams *p = state->input;
  
  /* In case the user incorrectly uses the equal sign (for example
     with a short format or with space in the long format, then `arg`
     start with (if the short version was called) or be (if the long
     version was called with a space) the equal sign. So, here we
     check if the first character of arg is the equal sign, then the
     user is warned and the program is stopped: */
  if(arg && arg[0]=='=')
    argp_error(state, "Incorrect use of the equal sign (`=`). For short "
	       "options, `=` should not be used and for long options, "
	       "there should be no space between the option, equal sign "
	       "and value.");
 
  switch(key)
    {
    /* Operating modes: */
    case 'q':
      p->verb=0;
      break;
    case 'r':
      p->onlycircum=1;
      break;
    case 'n':
      p->up.multip=0;
      break;
    case 'B':
      p->up.tmpblankmask=1;
      break;

    /* Input parameters: */
    case 'e':
      intelzero(arg, &p->up.imgext, "imgext", key);
      break;
    case 'a':
      sizetelzero(arg, &p->s1, "naxis0", key);
      break;
    case 'b':
      sizetelzero(arg, &p->s0, "naxis1", key);
      break;
    case 'm':
      p->maskname=arg;
      break;

    /* Catalog parameters: */
    case 'x':
      sizetelzero(arg, &p->up.ycol, "xcol", key);
      break;
    case 'y':
      sizetelzero(arg, &p->up.xcol, "ycol", key);
      break;
    case 'p':
      sizetelzero(arg, &p->up.pacol, "pacol", key);
      break;
    case 'j':
      sizetelzero(arg, &p->up.mjcol, "mjcol", key);
      break;
    case 'i':
      sizetelzero(arg, &p->up.micol, "micol", key);
      break;
    case 'u':
      sizetelzero(arg, &p->up.multipcol, "multipcol", key);
      break;      
      
    /* Read the non-option argument: */
    case ARGP_KEY_ARG:
      /* Since there are only two arguments, state->arg_num should
	 never be more than 2. Note that it starts from zero.*/
      if(state->arg_num >= 2)
	argp_error(state, "Too many arguments! ");

      /* See what type of input value it is and put it in. */
      if( strcmp(&arg[strlen(arg)-5], ".fits") )
	{
	  if(p->up.catname)
	    argp_error(state, "Only one catalog file can be given.");
	  else
	    p->up.catname=arg;
	}
      else
	{
	  if(p->up.imgname)
	    argp_error(state, "Only one FITS image should be given.");
	  else
	    p->up.imgname=arg;
	}	
      break;
      
    /* Make sure an argument is given: */
    case ARGP_KEY_END:
      if(state->arg_num==0)
	argp_error(state, "No argument given!");
      if(p->up.catname==NULL)
	argp_error(state, "No ASCII catalog provided.!");
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}





/* Basic structure defining the whole argument reading process. */
static struct argp argp = {options, parse_opt, args_doc, doc};


#endif
