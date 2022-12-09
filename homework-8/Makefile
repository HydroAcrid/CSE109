all: libpack109.a main
	mkdir -p build/objects/release
	mkdir -p build/lib/release

libpack109.a:
	g++ src/lib.cpp -c -Iinclude -std=c++11
	ar rs libpack109.a lib.o 
	mkdir -p build/lib/release
	mkdir -p build/objects/release
	mv *.o build/objects/release
	mv libpack109.a build/lib/release	

main:
	g++ src/bin/main.cpp -c -lpack109 -Lbuild/lib/release -Iinclude -std=c++11
	g++ main.o -o main -lpack109 -Lbuild/lib/release -std=c++11
	mkdir -p build/bin/release
	mv main.o build/objects/release
	mv main build/bin/release

clean:
	rm -f *.a
	rm -f *.o
	rm -rf build

