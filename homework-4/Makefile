all:
	gcc main.o -L . -l mylib -o main
main.o:
	cpp ./src/bin/main.c -I ./include > main.I
	cc main.i -S
libmylib.a:
	cpp ./src/mylib1.c > mylib1.i
	cpp ./src/mylib2.c > mylib2.i
	cc mylib1.i -S
	cc mylib2.i -S
	as mylib1.s -o mylib1.o
	as mylib2.s -o mylib2.o
	ar -rs libmylib.a mylib1.o mylib2.o
clean:
	rm *.i *.s *.a *.o main 

