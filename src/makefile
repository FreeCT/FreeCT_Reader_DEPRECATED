NVCC=nvcc
CC=gcc

ODIR=obj
IDIR=../include

CFLAGS= -g
LIBS=-lm

_OBJ=binary.o ctd.o dicom.o ptr.o siemens_ima.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ));

all: ../libfct_read.a

../libfct_read.a: $(OBJ)
	cd obj && ar rcs ../../libfct_read.a *.o
#	(cd obj && $(NVCC) -o ../../libfct_read.o *.o)

obj/binary.o: binary.c $(IDIR)/binary.h
	$(NVCC) $(CFLAGS) -c -o $@ $<

obj/ptr.o: ptr.c $(IDIR)/ptr.h
	$(NVCC) $(CFLAGS) -c -o $@ $<

obj/ctd.o: ctd.c $(IDIR)/ctd.h
	$(NVCC) $(CFLAGS) -c -o $@ $<

obj/siemens_ima.o: siemens_ima.c $(IDIR)/siemens_ima.h
	$(NVCC) $(CFLAGS) -c -o $@ $<

obj/dicom.o: dicom.c $(IDIR)/dicom.h
	$(NVCC) $(CFLAGS) -c -o $@ $<

.PHONY: all ../libfct_read.a clean

clean:
	rm obj/*.o
