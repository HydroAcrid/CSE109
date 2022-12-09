test: test.o libhashset.a
	g++ test.o -o tester -lhashset -llinkedlist -L. -Llib
	mkdir -p build/bin/release
	mkdir -p build/lib/release
	mkdir -p build/objects
	mv *.o build/objects
	mv *.a build/lib/release
	mv tester build/bin/release/test

test.o: test/test.cpp
	g++ test/test.cpp -c -I include -I lib

static:
	mkdir -p build/lib/release
	mkdir -p build/objects

	g++ main.cpp -c -I . 
	ar -rs libhashset.a templates.o

	mv libhashset.a build/lib/release
	mv templates.o build/objects

shared:
	mkdir -p build/bin
    mkdir -p build/objects

	cd ../ && \
	g++ src/main.cpp -I lib/hashset.h -c -fpic && \
    g++ -shared main.o -o libhashset.so && \

    mv liblinkedlist.o build/objects && \
    mv libhashset.so build/lib/release
	
debug:
	mkdir -p build/bin
    mkdir -p build/objects

	cd ../ && \
	g++ -g src/main.cpp -I lib/hashset.h -c -fpic && \
    g++ -shared main.o -o libhashset.so && \

    mv liblinkedlist.o build/objects && \
    mv libhashset.so build/lib/release

clean:
	rm -rf build

install:
	mv libhashset.so /usr/lib/

