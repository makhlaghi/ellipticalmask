EllipticalMask
==============

Place elliptical masks over an image or in a separate image.

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

Once you have unpacked the file, installing EllipticalMask is very
easy through the standard GNU method (`$` is for commands to be run as
a user and `#` is for those to be run as root for system wide install).

    $ ./configure
    $ make
    # make install

EllipticalMask accepts standard [POSIX+GNU style command line options]
(http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html#Argument-Syntax)
apply. To see the full list of options with a short explanaion of each
please run `$ ellipticalmask --help` or `$ ellipticalmask -?`

Comments and suggestions:
----------------------------------------

I hope EllipticalMask will be useful for you. If you find any
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

EllipticalMask is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

EllipticalMask is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with EllipticalMask.  If not, see <http://www.gnu.org/licenses/>.