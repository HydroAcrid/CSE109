#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//Checks for filename 
int search(char* filePath) {
  if(access(filePath, X_OK) == 0) {
    return 0;
  }
  
  return 1;
}