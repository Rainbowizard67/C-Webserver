#ifndef PREPROCESS_NETWORK
#define PREPROCESS_NETWORK

#include "settings.h"
#include "scurry_utils.h"
#include "project_headers.h"

//Start Macros, structures and global variables
#define BACKLOG 25
#define PORT 8080 //port number
#define MAX_POOL_SIZE 6
#define THREAD_THRESHOLD 800

volatile int active_requests = 0;

typedef struct sockaddr_in sockaddr_in;

//End Macros, structures, and global variables

#endif
