

all: clean build  run


run:
	cd build; ./Vega


build: clean
	mkdir build
	cd build/; qmake ../Vega.pro
	make -C build/
	cd build/; rm -rf *.o *.cpp *.cc *.h Makefile

install: build



uninstall:




check:
	cppcheck --language=c++ --suppress=missingIncludeSystem model/*.cc controller/*.cc model/*.h controller/*.h view/*.h view/*.cpp

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n model/*.cc controller/*.cc model/*.h controller/*.h
	rm -rf .clang-format



clean:
	rm -rf *.o *.a build
