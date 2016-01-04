CC=g++

ODIR=obj
IDIR=../include

CFLAGS= -g
LIBS=-lm

_OBJ=binary_read.o force_read.o definitionas_read.o sensation64_v1794_read.o sensation64_v2007_read.o dicom_read.o imawrapper_read.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ));

all: ../libfct_read.a

../libfct_read.a: $(OBJ)
	cd obj && ar rcs ../../libfct_read.a *.o

obj/binary_read.o: binary_read.cpp $(IDIR)/binary_read.h
	$(CC) $(CFLAGS) -c -o $@ $<

obj/force_read.o: force_read.cpp $(IDIR)/force_read.h
	$(CC) $(CFLAGS) -c -o $@ $<

obj/definitionas_read.o: definitionas_read.cpp $(IDIR)/definitionas_read.h
	$(CC) $(CFLAGS) -c -o $@ $<

obj/sensation64_v1794_read.o: sensation64_v1794_read.cpp $(IDIR)/sensation64_v1794_read.h
	$(CC) $(CFLAGS) -c -o $@ $<

obj/sensation64_v2007_read.o: sensation64_v2007_read.cpp $(IDIR)/sensation64_v2007_read.h
	$(CC) $(CFLAGS) -c -o $@ $<

obj/dicom_read.o: dicom_read.cpp $(IDIR)/dicom_read.h
	$(CC) $(CFLAGS) -c -o $@ $<

obj/imawrapper_read.o: imawrapper_read.cpp $(IDIR)/imawrapper_read.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all ../libfct_read.a clean

clean:
	rm obj/*.o
