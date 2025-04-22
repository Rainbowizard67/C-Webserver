#ifndef PREPROCESS_NETWORK
#define PREPROCESS_NETWORK

#include "settings.h"
#include "handleClient.h"
#include "project_headers.h"
#include "threadpool.h"

//Start Macros, structures and global variables
#define BACKLOG 25
#define PORT 8080 //port number
#define MAX_EVENTS 1024 //if you want to go higher change in /proc/sys/fs/file-max and set somaxconn

typedef struct sockaddr_in sockaddr_in;

//End Macros, structures, and global variables

#endif
