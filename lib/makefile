CC	= CC

.SUFFIXES : .o .cpp

.cpp.o:
	$(CC) -c $(CFLAGS) $*.cpp

LIBOBJS	= polhemus.o serial.o

CFLAGS= $(CC_OPT) $(OPT) -DSGI -DISOTRAK2 -I../include -o $*.o

all:	libpolhemus.a

polhemus.o:  polhemus.cpp ../include/polhemus.h
serial.o:  serial.cpp ../include/serial.h

libpolhemus.a: $(LIBOBJS) 
	ar r libpolhemus.a $(LIBOBJS)

