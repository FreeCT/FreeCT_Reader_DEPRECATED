INSTALL_PATH?=/usr/

all: rebuild

rebuild:
	mkdir -p src/obj
	$(MAKE) -C src ../libfct_read.a
	mkdir -p build
	cp include/* build/
	cp libfct_read.a build/
	rm -f libfct_read.a

install:
ifneq ($(USER),root)
	@echo Please run with sudo
else
	mkdir -p $(INSTALL_PATH)include/fct
	mkdir -p $(INSTALL_PATH)include/fct/include/
	cp build/libfct_read.a $(INSTALL_PATH)lib/
	mv build/fct_read.h $(INSTALL_PATH)include/fct/
	cp build/*.h $(INSTALL_PATH)include/fct/include/
endif

uninstall:
ifneq ($(USER),root)
	@echo Please run with sudo
else
	rm $(INSTALL_PATH)include/fct/fct_read.h
	rm $(INSTALL_PATH)include/fct/include/ptr.h
	rm $(INSTALL_PATH)include/fct/include/ctd.h
	rm $(INSTALL_PATH)include/fct/include/dicom.h
	rm $(INSTALL_PATH)include/fct/include/siemens_ima.h
	rm $(INSTALL_PATH)include/fct/include/binary.h
	rmdir $(INSTALL_PATH)include/fct/include
	rmdir $(INSTALL_PATH)include/fct
	rm $(INSTALL_PATH)lib/libfct_read.a
endif

.PHONY: all install uninstall clean

clean:
	$(MAKE) -C src clean
	rm -rf build/
