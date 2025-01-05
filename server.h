#ifndef PREPROCESS_NETWORK
#define PREPROCESS_NETWORK

#include<stdio.h> //standard I/O ouput
#include<stdlib.h> //standard C library
#include<stdbool.h> //standard boolean library
#include<string.h> //standard string library
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h> //standard Unix OS library
#include<pthread.h> //standard C thread library

#include"handleClient.h"


// Macros and global variables
#define backlog 10
#define PORT 8080 //port number
#define buffer 1024 //exactly one KB

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
