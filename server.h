#ifndef PREPROCESS_NETWORK
#define PREPROCESS_NETWORK

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>


// Macros and global variables
#define backlog 10
#define PORT 8080
#define buffer 1024 //exactly one KB

#endif