EllipticalMask
==============

Place elliptical masks over an image.

Description
-----------

Given a certain catalog (for example one that is output by
SExtractor), this small program will mask all the pixels within an
ellipse defined by the catalog. It can also use the size of the image
to make a mask image (where all pixels belonging to objects are
labeled with 1 and all those that are not are labeled zero.  It can
also create a masked image with any size, with ellipses that are
totally out of the image being ignored and those that are partially in
only getting partially filled.



Requirements
------------

[cfitsio](http://heasarc.nasa.gov/fitsio/fitsio.html) For reading and
  writing FITS files. I have explained [how to install `cfitsio`
  here](http://www.astr.tohoku.ac.jp/~akhlaghi/cfitsiowcslibinstall.html)



Installing and running
----------------------

Once you have `cfitsio` installed, all you need to do is to navigate
to the folder you downloaded this source code to and run `make` in it.
It will compile the code and put make an executable file. If you want
to be able to access the file system wide, you have to change to root
(super user) and then run `make install`. 

You can configure `ellipticalmask` with these options.  The [POSIX
argument syntax
conventions](http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html#Argument-Syntax)
apply.


Options that don't run `ellipticalmask`:
* `-h`: View details and default values of all the options.
* `-v`: View only version and copyright information.

On/Off options: 

* `-z`: Get the sizes of the input image, but use a
  zero valued image to build the mask on.
* `-s`: Print the average and standard deviation 
  of un masked regions.
* `-r`: Only mask the circumference of each ellipse.
  not the whole inner area which is masked as default.

Options with arguments (run `ellipticalmask -h` to view default values.)
* `-x`: NAXIS1 size (width as seen in ds9) of the image.
* `-y`: NAXIS2 size (height as seen in ds9) of the image.
* `-i`: Input catalog (ASCII table) name.
* `-I`: Input FITS image name.
* `-o`: Output FITS image (mask) name.
* `-a`: Catalog column for Ellipse's center on NAXIS1.
* `-b`: Catalog column for Ellipse's center on NAXIS2.
* `-c`: Catalog column for Ellipse's position angle.
* `-d`: Catalog column for Ellipse's major axis.
* `-e`: Catalog column for Ellipse's minor axis.
* `-f`: Catalog column for a multiple to the major axis.

This last option is for dealing with SExtractor's output, where the
desired Kron radius is in units of the major or minor axis. If you
know you major and minor axises before hand, you can simply set this
value to 1 for all your profiles. 


Comments and suggestions:
----------------------------------------

I hope `ellipticalmask` will be useful for you. If you find any
problems in it please contact me so I can correct them. I would also
be very glad to hear any suggestions or comments you might have, thank
you.

makhlaghi@gmail.com 

akhlaghi@astr.tohoku.ac.jp

http://astr.tohoku.ac.jp/~akhlaghi/

----------------------------------------
Copyright:
----------------------------------------
Copyright (C) 2014 Mohammad Akhlaghi

Tohoku University Astronomical Institute

http://astr.tohoku.ac.jp/~akhlaghi/

`ellipticalmask` is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

`ellipticalmask` is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with `ellipticalmask`.  If not, see <http://www.gnu.org/licenses/>.