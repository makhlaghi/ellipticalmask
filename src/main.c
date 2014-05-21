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

#include "ellipticalmask.h"
#include "ui.h"

int
main(int argc, char *argv[])
{
  struct elmaskparams p;
  getsaveoptions(&p, argc, argv);

  ellipmask(&p);

  free(p.intable);
  if(p.img) free(p.img);
  return 0;
}
