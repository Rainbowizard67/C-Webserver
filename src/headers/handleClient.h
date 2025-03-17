#ifndef PREPROCESS_HANDLECLIENT
#define PREPROCESS_HANDLECLIENT

#include "../headers/project_headers.h"
#include "../headers/fileLoader.h"

#define BUFFER_SIZE 2048 //2 KB

void http_client_handler(int soc, struct sockaddr_storage client, socklen_t size);

#endif
