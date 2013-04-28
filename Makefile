#
# Makefile for NFF to SFF converter 
#

PROG=nff2sff
CC=gcc
CFLAGS=-O -s
YACC=bison
YFLAGS=-y -d

CSRC=data.c color.c sff.c objects.c nff.c tokens.c
COBJ=data.o color.o sff.o objects.o nff.o tokens.o

OSRC=nff.y tokens.l
OOBJ=nff.o tokens.o
HDRS=defs.h extern.h config.h y.tab.h
LIBS=m

$(PROG):	$(COBJ) $(OOBJ)
	$(CC) -O -s -o $(PROG) $(COBJ) $(OOBJ) -l$(LIBS)

data.o: data.c defs.h config.h 
	$(CC) $(CFLAGS) -c $*.c

color.o: color.c defs.h
	$(CC) $(CFLAGS) -c $*.c

sff.o: sff.c data.c defs.h config.h extern.h
	$(CC) $(CFLAGS) -c $*.c

objects.o: objects.c data.c defs.h config.h extern.h
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f $(COBJ) $(OOBJ)
	rm -f core tags

cleanall:
	rm -f $(COBJ) $(OOBJ)
	rm -f core tags
	rm -f $(HDRS) $(CSRC) $(OSRC)

lint:
	lint $(CSRC)

archive:
	rm -f sff.tar*
	tar cvf - $(HDRS) $(CSRC) $(OSRC)|compress >sff.tar.Z

extract:
	zcat sff.tar|tar xvf - $(HDRS) $(CSRC) $(OSRC)
