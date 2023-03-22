all: clean build 

run:
	cd build; ./Vega_absolut

build: clean
	mkdir build
	cp config.ini build/config.ini
	cd build/; qmake ../Vega_absolut.pro
	make -C build/
	cd build/; rm -rf *.o *.cpp *.cc *.h Makefile


clean:
	rm -rf *.o *.a build
