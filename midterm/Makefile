all: shared bin 

static:
	gcc src/lib.c -I include -c
	ar -rs libmyls.a lib.o
	mkdir -p build/lib
	mkdir -p build/objects
	mv lib.o build/objects/lib.o
	mv libmyls.a build/lib

shared:
	gcc src/lib.c -c -fpic -I include
	gcc -shared lib.o -o libmyls.so
	mkdir -p build/lib
	mkdir -p build/objects
	mv lib.o build/objects/lib.o
	mv libmyls.so build/lib

bin: static
	gcc src/bin/main.c -I include -L build/lib -l myls -o my_ls
	mkdir -p build/bin
	mv my_ls build/bin/

install: shared
	mkdir -p usr/lib
	mv build/lib/libmyls.so usr/lib/libmyls.so

clean:
	rm -rf build/ usr/
	
