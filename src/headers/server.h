#ifndef PREPROCESS_NETWORK
#define PREPROCESS_NETWORK

#include <signal.h>
#include "settings.h"
#include "handleClient.h"
#include "project_headers.h"
#include "threadpool.h"

//Macros and global variables
#define BACKLOG 25
#define PORT 8080 //port number
#define INIT_TPOOL_NUM 5
#define MAX_EVENTS 50

typedef struct sockaddr_in sockaddr_in;
//End Macros and global variables

#endif
