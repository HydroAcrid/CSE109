#include <vector>
#include <stdio.h>
#include "pack109.hpp"
#include <stdlib.h>
#include <stdexcept>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream> 

#define KEY 42

using namespace std;



//Checks to see if the file exists or not 
bool file_exist(char* path) {
    int exist = access(path, F_OK);
    if(exist == -1) {
        return false;
    }
    else {
        return true;
    }
}

char* decrypt(char* input) {
    for(int i = 0; i < strlen(input); i++) {
        input[i] = input[i] ^ KEY;
    }

    //cout << "Orginal text: \n" << input;
    printf("%s\n", input);

    return input;
}

int main(int argc, char* argv[]) {
  int portnum = 0;
  int iter = 0;
  int socktfd = 0;
  int flag = 0;
  char buffer[256];
  string str = "";

  struct hostent* server;
  struct socktAddrInput;
  struct sockaddr_in serverAddr;

  //Checks to see hostname address:port flag
  if (strcmp(argv[1], "--hostname") != 0 || strstr(argv[2], ":") == nullptr || argc < 3) { 
      fprintf(stderr,"enter --hostname address:port \n");
      exit(0);
  }

  //Checks to see --send flag, --request flag, and no 
  if(argc > 4) {
      if(strcmp(argv[3], "--send") == 0) {
          flag = 1;
          cout << "SEND FLAG RECIEVED\n";
      }

      else if(strcmp(argv[3], "--request") == 0) {
          flag = 2;
          cout << "REQUEST FLAG RECIEVED\n";

      }

      else {
          cout << "Improper flags. ERROR YOU ARE BUGGIN. \n";

      }

      printf("%d\n",flag);

  }

  //server port allocation 
  str = argv[2];  
  size_t pos = str.find(":");
  string port = str.substr(pos+1);
  char charStrLim[256];
  
  strcpy(charStrLim, port.c_str());
//   printf("%s\n", charStrLim);
  portnum = atoi(charStrLim);
  std::cout<<"portnum: "<<portnum<<'\n';

  //create socket port
  socktfd = socket(AF_INET, SOCK_STREAM, 0);
  if(socktfd < 0) {
      cout << "ERROR socket not opened \n";
      perror("ERROR socket not opened");
      exit(1);
  }

  //Getting the host
  string host = str.substr(0,pos);
  char charstr[1000];
  strcpy(charstr, host.c_str());
  printf("%s\n",charstr);
  server = gethostbyname(charstr);

  //Checks to see if there is a host
  if(server == nullptr) {
      cout << "HOST ERROR. Cannot find \n";
  }

  //Clears server address
  bzero((char*) &serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;

  //Copying byte sequence 
  bcopy((char*) server -> h_addr, (char*) &serverAddr.sin_addr.s_addr, server -> h_length);
  serverAddr.sin_port = htons(portnum);


  //Connecting to server 
  if(connect(socktfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
      perror("SERVER ERROR");
      exit(1);
  }
  else {
      cout << "SUCCESS. Connected! \n";
  }

  //Serializing and sending the file 
  if(flag == 1) {
      cout << "SEND A FILE \n";

      if(file_exist(argv[4])) {
          FILE* input; 
          char* buffer;
          size_t copy;
          long fileSize;

          //open file 
          cout << "Opening file \n";
          input = fopen(argv[4], "r");

          //Checks if there is a file
          if(input == nullptr) {
              cout << "FILE ERROR. \n";
              exit(1);
          }

          //Find file size. Uses fseek to scan the file in order to find the size. then rewinds to beg 
          fseek(input, 0, SEEK_END);
          fileSize = ftell(input);
          rewind(input);

          //Allocates memory for file. Checks if successful 
          buffer = (char*) malloc (sizeof(char) *fileSize);
          if(buffer == nullptr) {
              cout << "BUFFER ERROR \n";
              exit(1);
          }
          
          //Copies files into buffer. Checks if copy is correct  
          copy = fread(buffer, 1, fileSize,input);
          if(copy != fileSize) {
              cout << "COPY ERROR \n";
              exit(1);
          }

          //Prints out the copy  
          cout << "Copy initiating... \n" << copy << endl;

          //Storing file
          cout << "Storing file... \n";
          File fStore;
          vec bytes(buffer, buffer + fileSize); //This line might be broken 
          fStore.name = argv[4];
          fStore.array = bytes;

          //Serialization of file
          vector<u8> fileSer = pack109::serialize(fStore);
          size_t serLen = fileSer.size();
          pack109::printVec(fileSer);

          //Encryption of file 
          cout << "Encrypting file... \n";
          char fileEnc[10000];
          std::copy(fileSer.begin(), fileSer.end(), fileEnc);
        //   encrypt(fileEnc, serLen);

        for (int i = 0; i < serLen; i++) {
            fileEnc[i] ^= KEY;
        }

          //File sending
          cout << "File ready to be sent \n";

          //Message is sent to server 
          iter = write(socktfd, fileEnc, serLen);
          if(iter < 0) {
              cout << "SOCKET WRITING ERROR \n";
              exit(1);
          }
          else {
              cout << "File sent \n";
          }

          //Freeing 
          fclose(input);
          free(buffer);

          

      }
      else {
          cout << "File does not exist \n";
      }

  }

  else if(flag == 2) {

    cout << "Creating request... \n";
    Pull p;  
    p.name = argv[4];
    std::vector<u8> serialP = pack109::serialize(p);
    pack109::printVec(serialP);
    size_t lengthP = serialP.size(); 

    //Encrypting 
    cout << "Encrypting request... \n";
    char pullEnc[10000];
    std::copy(serialP.begin(), serialP.end(), pullEnc);
    // encrypt(pullEnc,lengthP);

    for(int i=0; i < lengthP; i++) {
            pullEnc[i] = pullEnc[i] ^ KEY;
    }
    printf("%s\n", pullEnc);

    //Request sending 
    cout << "Request ready to be sent \n";

    //Message is sent to server
    iter = write(socktfd, pullEnc, lengthP);
    if(iter < 0) {
        cout << "SOCKET WRITING ERROR \n";
        exit(1);
    }
    else {
        cout << "Request sent \n";
    }

    //Recieving and Decrypting section 
    char pullBuff[10000];
    iter = read(socktfd, pullBuff, 10000);

    if(iter < 0) {
        cout << "RECIEVING ERROR \n";
        exit(1);
    }
    
    cout << "\n" << pullBuff; //this doesnt happen 
    cout << "Decrypting... \n";
    //decrypt(pullBuff);  //program ends here

    for(int i=0; i < strlen(pullBuff); i++) {
        pullBuff[i] = pullBuff[i] ^ KEY;
    }

    printf("%s\n", pullBuff);

    //Deserializing section 
    vector<u8> bytesDe;
    for(int i = 0; i < strlen(pullBuff); i++) {
        bytesDe.push_back(pullBuff[i]);
    }
    File fileDe = pack109::deserialize_file(bytesDe);

    //Saving the file 
    cout << "Saving the file... \n";

    string filename = fileDe.name;
    string path = "Recieved:";

    string newPath = path + filename;
    const char* truePath = newPath.c_str(); //c_str converts the string to an array of characters

    std::ofstream outfile(truePath);
    outfile.write((const char*)fileDe.array.data(), fileDe.array.size());

    cout << "File saved successfully! \n";

  }

  return 0;

}

//Encrypts the file 
// string encrypt(string input) {

//     for (int i = 0; input[i] != '\0'; i++) {
// 		  input[i] = input[i] ^ KEY;
// 	  }

//     // printf("Encrypted text: %s\n", input);
//     cout << "Encrypted text: \n" << input;
//     return input;

// }

char* encrypt(char* input, size_t length) {
    for(int i = 0; i < length; i++) {
        input[i] = input[i] ^ KEY;
    }

    // printf("Encrypted text: %s\n", input);
    cout << "Encrypted text: \n" << input;
    printf("%s\n", input);
    return input;
}

//Decrypts the file
string decrypt(string input) {
    for (int i = 0; input[i] != '\0'; i++) {
		    input[i] = input[i] ^ KEY;
	  }
	
    cout << "Original text: \n" << input;
    return input;
}






