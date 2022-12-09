#include <stdlib.h>
#include <stdio.h>


void multiply_ptrs(int* x, int* y, int* z) {
    *z = *x * *y;
    printf("%d\n", *z);

}


int main(int argc, char** argv) {
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    int z;
    multiply_ptrs(&x, &y, &z);

    return 0;

}