#ifndef PREPROCESS_NETWORK
#define PREPROCESS_NETWORK

#include "netData.h"
#include "handleClient.h"
#include "project_headers.h"


// Macros and global variables
#define backlog 25
#define PORT 8080 //port number
#define buffer 10240 //exactly ten KBs

#endif

//Structs

/* struct sockaddr_in {
    short int sin_family;   //Address Family (Ex: AF_INET)
    unsigned short int sin_port;    //Port number
    struct in_addr sin_addr;    //IPv4 address
    unsigned char sin_zero[8];  //Padding
   };
*/

/*  struct in_addr {
        unsigned long s_addr; //32-bit Ipv4 address in Network order
    };
*/
