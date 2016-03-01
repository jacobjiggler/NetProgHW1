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
  struct addrinfo hints;
  struct addrinfo * result;

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype=SOCK_DGRAM;
  hints.ai_protocol=0;
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me // consider removing so you dont use bind

    if (argc !=  5){
      std::cout << "bad arguments" << std::endl;
      return 1;
    }
    char* address = argv[1];
    char* myID = argv[1];
    char* peerID = argv[1];
    char* message = argv[1];


    int err=getaddrinfo(address,PORT,&hints,&result);
    if (err!=0) {
        std::cout << "failed to resolve remote socket address " << err << std::endl;
    }

    //first do inet_pton with ipv4


    //past to getaddrinfo
    //getaddrinfo

    return 0;
}
