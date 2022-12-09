#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

   printf("%p\n", &argv);
   for(int i = 0; i < argc; i++) {
       printf("%p\n", &argv[i]);

   } 

   for(int i = 0; i < argc; i++) {

       for(int k = 0; argv[i][k] != '\0'; k++) {
            printf("%p\n", &argv[i][k]);
       }

   } 
  // Implement me
  return 0;
}