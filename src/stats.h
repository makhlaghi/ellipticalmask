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
#ifndef STATS_H
#define STATS_H

#define MAXFD 1e30
#define MINFD -1e30

void
favestd(float *in, size_t size, float *ave, float *std, 
	size_t *unmaskedsize, unsigned char *mask);

void
floatmin(float *in, size_t size, float *min);


#endif
