#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h> //standard I/O ouput
#include <stdlib.h> //standard C library
#include <stdbool.h> //standard boolean library
#include <string.h> //standard string library
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h> //standard Unix OS library
#include <pthread.h> //standard C thread library
#include <semaphore.h>
#include <sys/resource.h>

#define MAX_BUFFER_SIZE 4096
#define MAX_URL_SIZE 256

//Start State machine
typedef enum conn_state_t {
    STATE_READ,
    STATE_PARSE,
    STATE_HANDLE,
    STATE_WRITE,
    STATE_CLOSE
}conn_state_t;

typedef struct client_connection_t {
    int client_socket;
    struct sockaddr_storage client_addr;
    socklen_t client_len;
    conn_state_t state;
    char buffer[MAX_BUFFER_SIZE];
    size_t buffer_len;
    char method[16];
    char path[MAX_URL_SIZE];
    char response[BUFSIZ];
    size_t response_len;
    size_t bytes_sent;
    bool keep_alive;
}client_connection_t;

//End State machine


#endif