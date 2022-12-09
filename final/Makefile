all: libpack109.a server

libpack109.a: lib.o
	ar rs libpack109.a lib.o
	mkdir -p build/lib/release
	mkdir -p build/objects/release
	mv *.o build/objects/release
	mv libpack109.a build/lib/release	

lib.o: src/lib.cpp
	g++ src/lib.cpp -c -Iinclude -std=c++11

server: server.o
	g++ server.o -o server -lpack109 -Lbuild/lib/release -std=c++11
	mkdir -p build/bin/release
	mv server.o build/objects/release
	mv server build/bin/release

server.o: src/bin/server.cpp
	g++ src/bin/server.cpp -c -lpack109 -Lbuild/lib/release -Iinclude -std=c++11

clean:
	rm -f *.a
	rm -f *.o
	rm -rf build
