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
#define PORT 12345



//client serveraddress mypeerid contactpeerid message
int main(int argc , char *argv[])
{
  struct addrinfo hints;
  struct addrinfo * result;


    if (argc !=  5){
      std::cout << "bad arguments" << std::endl;
      return 1;
    }
    char* address = argv[1];
    char* myID = argv[1];
    char* peerID = argv[1];
    char* message = argv[1];


    //first do inet_pton with ipv4
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (
    inet_pton(AF_INET, argv[1], &addr.sin_addr) != 1
    ) {
      //if that fails then inet_pton with ipv6
      struct sockaddr_in6 addr;
      addr.sin6_family = AF_INET6;
      addr.sin6_port = htons(12345);
      if (
      inet_pton(AF_INET6, argv[1], &addr.sin6_addr) != 1
      ) {
        memset(&hints, 0, sizeof(hints));
        
      	std::cout << "probably a hostname" << std::endl;
      }

    }

    //past to getaddrinfo
    //getaddrinfo

    return 0;
}
