#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/mman.h>
#include <sys/uio.h>
#define PORT "12345"



//client serveraddress mypeerid contactpeerid message
int main(int argc , char *argv[])
{

  if (argc !=  5){
    std::cout << "bad arguments" << std::endl;
    return 1;
  }

  struct addrinfo hints;
  struct addrinfo * result;

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype=SOCK_DGRAM;
  hints.ai_protocol=0;
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me // consider removing so you dont use bind

  char* address = argv[1];
  std::string myID = argv[2];
  std::string peerID = argv[3];
  char* message = argv[4];
  std::string reg = "REGISTER " + myID;
  std::string get = "GET_ADDR " + peerID;


    int err=getaddrinfo(address,PORT,&hints,&result);
    if (err!=0) {
        std::cout << "failed to resolve remote socket address " << err << std::endl;
        exit(1);
    }
    int sock;
    //socket(domain,type,protocol)
    if ((sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1) {
              perror("Socket");
              exit(1);
          }
    if (sendto(sock, reg.c_str(), reg.size(), 0, result->ai_addr, result->ai_addrlen )==-1){
      std::cout << "something went wrong" << std::endl;
      exit(1);
    }
    if (sendto(sock, get.c_str(), get.size(), 0, result->ai_addr, result->ai_addrlen )==-1){
      std::cout << "something went wrong" << std::endl;
      exit(1);
    }
    char buffer[200];
    int byte_count = recvfrom(sock,buffer,sizeof(buffer),0,result->ai_addr, &result->ai_addrlen);
    if (byte_count <=0){
      std::cout << "something went wrong receiving" << std::endl;
      exit(1);
    }
    std::string a = "NOT FOUND";
    if (strcmp(buffer,a.c_str())==0){
      std::cout << "NOT FOUND JERKWAD" << std::endl;
    }
    else {
      char* addr;
      const char* delim = " ";
      char* port;
      addr = strtok(buffer,delim);
      port = strtok(NULL,delim);
      std::cout << port << std::endl;
      int err=getaddrinfo(addr,port,&hints,&result);
      if (err!=0) {
          std::cout << "failed to resolve remote socket address " << err << std::endl;
      }
      int sock2;
      //socket(domain,type,protocol)
      if ((sock2 = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1) {
                perror("Socket");
                exit(1);
            }
      if (sendto(sock2, message, sizeof(message), 0, result->ai_addr, result->ai_addrlen )==-1){
        std::cout << "something went wrong" << std::endl;
      }
    }
    //lol
    while(1){
    memset(buffer, 0, sizeof(char)*200);
    byte_count = recvfrom(sock,buffer,sizeof(buffer),0,result->ai_addr, &result->ai_addrlen);
    if (byte_count <=0){
      std::cout << "something went wrong receiving" << std::endl;
    }
    std::cout << buffer << std::endl;
}


    return 0;
}
