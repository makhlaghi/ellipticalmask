src=./src

objects=main.o ellipticalmask.o ui.o attaavv.o fitsarrayvv.o \
	arraymanip.o raddist.o sll.o pix.o stats.o

vpath %.h $(src)
vpath %.c $(src)

CC=gcc
CFLAGS=-Wall -W -O -pedantic -I$(src)
LDLIBS=-lcfitsio -pthread -lm

mockgals: $(objects) 
	@$(CC) -o ellipticalmask $(objects) $(LDLIBS) 
	@rm *.o
#	./ellipticalmask -s -iSEresults.txt -I1.fits -c8 -d9 -e10 -f6

.SILENT: $(objects)

.PHONY: install

install:
	cp ./ellipticalmask /usr/local/bin/
