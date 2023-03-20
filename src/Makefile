

all: clean build  run


run:
	cd build; ./Vega_absolut


build: clean
	mkdir build
	cd build/; qmake ../Vega_absolut.pro
	make -C build/
	cd build/; rm -rf *.o *.cpp *.cc *.h Makefile

install: build


sql:
	cd /home/tls/Qt5.9.8/5.9.8/gcc_64/plugins/sqldrivers
	qmake "LIBS+=-L/usr/lib/x86_64-linux-gnu -lmysqlclient" mysql.pro
	make
	make install
uninstall:




check:
	cppcheck --language=c++ --suppress=missingIncludeSystem model/*.cc controller/*.cc model/*.h controller/*.h view/*.h view/*.cpp

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n model/*.cc controller/*.cc model/*.h controller/*.h
	rm -rf .clang-format



clean:
	rm -rf *.o *.a build
