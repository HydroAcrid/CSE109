
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my_which.h"

//Checks for filename 
int search(char* filePath) {
  if(access(filePath, X_OK) == 0) {
    return 0;
  }
  
  return 1;
}

int main(int argc, char* const argv[]) { //argc is the number of inputs while char** is a double array 
  char* path = getenv("PATH");
  int len = strlen(path);
  char temp[len];
  char* token;
  char** paths = (char**) malloc(500);
  int i = 0;
  int check = 1;
  int result = 0;
  int fileExist = 1;
    

//Separates the directories
  strcpy(temp, path);
  token = strtok(temp, ":");
    while(token != NULL) {
      paths[i] = token; // strdup(token)
      token = strtok(NULL, ":"); 
      i++;

  }

//Adds "/" to the directories 
  char extra[len];
  int j = i;
  // for(int i = 0; i < j ; i++) {
  //   strcpy(extra, paths[i]);
  //   strcat(extra, "/");
  //   //printf("%s\n", extra);
  // }

  
  //Adds filename to path variable 
  for(int i = 1; i < argc ; i++) {
    
    if(i == 1 && argv[1][0] == '-') {
      
      if(strcmp(argv[1], "-a") == 0) {
        check = 0;
        continue;
      }
      else {
        return 2;
      }
    }
    for(int k = 0; k < j; k++) {
      strcpy(extra, paths[k]);
      strcat(extra, "/");
      strcat(extra, argv[i]);

      //printf("%s\n", extra);
      if(search(extra) == 0) {
        printf("%s\n", extra);
        fileExist = 0;
        if(check == 0) {
          break;
        }
      }
    

    }

    if(fileExist != 0) {
      result = 1;
    }
  }


  return result;
}



//STRTOK use this!!!!!
//memoization USE THIS!!!
