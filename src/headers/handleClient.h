#ifndef PREPROCESS_HANDLECLIENT
#define PREPROCESS_HANDLECLIENT

#include "../headers/project_headers.h"
#include "../headers/fileLoader.h"

#define MAX_BUFFER_SIZE 2048 //2 KB
#define MAX_URL_SIZE 256

void http_client_handler(int soc, struct sockaddr_storage client, socklen_t size);

#endif
