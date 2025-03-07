#ifndef PREPROCESS_NETWORK
#define PREPROCESS_NETWORK

#include "netData.h"
#include "handleClient.h"
#include "project_headers.h"
#include "threadpool.h"

// Macros and global variables
#define BACKLOG 25
#define PORT 8080 //port number
#define BUFFER_LEN 10240 //exactly ten KBs
// End Macros and global variables

#endif

//Structs

/* struct sockaddr_in {
    short int sin_family;   //Address Family (Ex: AF_INET)
    unsigned short int sin_port;    //Port number
    struct in_addr sin_addr;    //IPv4 address
    unsigned char sin_zero[8];  //Padding
   };
*/
