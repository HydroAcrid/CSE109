#include <stdio.h>
#include "pack109.hpp"
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define KEY 42;

int main(int argc, char* argv[]) {
  int flag = 0;
  int portnum = 0;
  struct sockaddr_in serverAddr;
  int socktfd = 0;
  string str = "";


  //Checks to see hostname address:port flag and prints it out 
  if (strcmp(argv[1], "--hostname") != 0 || strstr(argv[2], ":") == nullptr || argc < 3) { 
    fprintf(stderr,"enter --hostname address:port \n");
    exit(0);
  }
      
  printf("%d\n",flag);

  //Creates a socket 
  socktfd = socket(AF_INET, SOCK_STREAM, 0); 
  if(socktfd < 0) {
    perror("SOCKET ERROR. CANNOT CREATE SOCKET");
    exit(1);
  }
  else {
    std::cout << "Socket Success!" << std::endl;
  }

  //Binds socket to a port 
  portnum = 8081;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(portnum);


  if (bind(socktfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
    perror("BINDING ERROR. CANNOT BIND");
    exit(1);
  }
  else {
    std::cout << "Binding success!" << std::endl; 
  }

  //Listening for a connection. Current server can host 5 connections at a time
  listen(socktfd, 5);  
  std::cout << "Listening on port:" << portnum << std::endl; 

  
  

















  return 0;
};

// #include <iostream>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>

// int main() {
//   // Create a socket
//   int sockfd = socket(AF_INET, SOCK_STREAM, 0);

//   // Bind the socket to a port
//   struct sockaddr_in serverAddr;
//   serverAddr.sin_family = AF_INET;
//   serverAddr.sin_addr.s_addr = INADDR_ANY;
//   serverAddr.sin_port = htons(8080);

//   bind(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

//   // Listen for connections
//   listen(sockfd, 5);

//   std::cout << "Listening on port 8080" << std::endl;

//   // Accept a connection
//   int clientfd = accept(sockfd, (struct sockaddr*) NULL, NULL);

//   std::cout << "Accepted connection" << std::endl;

//   // Send a message to the client
//   const char* message = "Hello, client!\n";
//   send(clientfd, message, strlen(message), 0);

//   // Close the client and server sockets
//   close(clientfd);
//   close(sockfd);

//   return 0;

// };


