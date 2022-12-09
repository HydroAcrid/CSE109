#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 
int strln(char* str) {
  int length = 0;
  for(int i = 0; str[i]!= '\0'; i++) {
    length++;
  }
  printf("%d\n", length);

  return length;
}

int main(int argc, char** argv) {
    char* input = argv[1];
    strln(input);

    return 0;
}