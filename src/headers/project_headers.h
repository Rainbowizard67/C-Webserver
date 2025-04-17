#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h> //standard I/O ouput
#include <stdlib.h> //standard C library
#include <stdbool.h> //standard boolean library
#include <string.h> //standard string library
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h> //standard Unix OS library
#include <pthread.h> //standard C thread library

//Start structures
typedef struct client_request_t {
    int client_socket;
    struct sockaddr_storage client_addr;
    socklen_t client_len;
}client_request_t;
//End structures

#endif