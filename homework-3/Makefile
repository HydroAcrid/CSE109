all: 
	#build the executable, link to libmylib.a
	gcc src/main.c -I src -o my_which -L build/bin -l my_which

	#move executable to bin directory
	mv my_which build/bin/

static:
	#build my_function.o
	gcc src/my_which_lib.c -c -I src 

	#build libmy_which.a
	ar -rs libmy_which.a my_which_lib.o

	#move build artifacts
	mkdir -p build/bin
	mkdir -p build/objects
	mv my_which_lib.o build/objects/my_which_lib.o
	mv libmy_which.a build/bin

shared:
	#compiles `my_which_lib.c` into a shared library called `libmy_which.so`.
	gcc src/my_which_lib.c -c -I src -fpic

	#build libmy_which.a
	gcc -shared -o libmy_which.so my_which_lib.o

	#move build artifacts
	mkdir -p build/bin
	mkdir -p build/objects
	mv my_which_lib.o build/objects/my_which_lib.o
	mv libmy_which.so build/bin


clean:
	rm -rf build
