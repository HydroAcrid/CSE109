static:
	mkdir -p build/lib/release
	mkdir -p build/objects

	g++ lib.cpp -c -I . 
	ar -rs liblinkedlist.a templates.o

	mv liblinkedlist.a build/lib/release
	mv templates.o build/objects

shared:
	mkdir -p build/bin
    mkdir -p build/objects

	cd ../ && \
	g++ src/lib.cpp -I lib/linkedlist.h -c -fpic && \
    g++ -shared lib.o -o liblinkedlist.so && \

    mv liblinkedlist.o lib/build/lib/release && \
    mv lib.so lib/build/objects

debug:
	mkdir -p build/bin
    mkdir -p build/objects

	cd ../ && \
	g++  -g src/lib.cpp -I lib/linkedlist.h -c -fpic && \
    g++ -shared lib.o -o liblinkedlist.so && \

    mv liblinkedlist.o lib/build/lib/release && \
    mv lib.so lib/build/objects

clean:
	rm -rf build
	