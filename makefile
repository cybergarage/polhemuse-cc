CC = CC
CC_OPT =	

LIBS =		-lmalloc -limage -lspaceball -lmpc -lm -lfpe
XLIBS =		-lXm -lXt -lX11

CFLAGS= $(CC_OPT) $(OPT) -DSGI -DISOTRAK2 -I./include -o $*.o

OBJS = sample.o

.SUFFIXES : .o .cpp

.cpp.o:
	$(CC) -c $(CFLAGS) $*.cpp


all:	sample

sample: $(OBJS) ./lib/libpolhemus.a
	CC -L./lib -o sample $(OBJS) -lpolhemus
