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

#include "sll.h"


/****************************************************************
 *****************           size_t          ********************
 ****************************************************************/
void
add_to_ssll(struct ssll **list, size_t value)
{
  struct ssll *newnode;

  newnode=malloc(sizeof *newnode);
  assert(newnode!=NULL);

  newnode->v=value;
  newnode->next=*list;
  *list=newnode;
}





void
pop_from_ssll(struct ssll **list, size_t *value)
{
  struct ssll *tmp;
  tmp=*list;
  *value=tmp->v;
  *list=tmp->next;
  free(tmp);
}





size_t
numinssll(struct ssll *list)
{
  size_t num=0;
  struct ssll *tmp;
  for(tmp=list;tmp!=NULL;tmp=tmp->next)
    num++;
  return num;
}





void
sslltoarray(struct ssll *list, size_t **f, size_t *num)
{
  size_t i=0, *tf;
  struct ssll *tmp;
 
  *num=numinssll(list);
  *f=malloc(*num*sizeof(size_t));
  assert(*f!=NULL);
  tf=*f;
    
  for(tmp=list;tmp!=NULL;tmp=tmp->next)
    tf[i++]=tmp->v;
}





void
freessll(struct ssll *list)
{
  struct ssll *tmp, *ttmp;
  tmp=list;
  while(tmp!=NULL)
    {
      ttmp=tmp->next;
      free(tmp);
      tmp=ttmp;
    }
}
