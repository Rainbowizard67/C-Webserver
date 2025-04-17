#ifndef PREPROCESS_HANDLECLIENT
#define PREPROCESS_HANDLECLIENT

#include "../headers/project_headers.h"
#include "../headers/fileLoader.h"
#include "../headers/hashTable.h"

#define MAX_BUFFER_SIZE 2048 //2 KB
#define MAX_URL_SIZE 256
#define MAX_CACHE_SIZE 5

void http_client_handler(client_request_t* client);

#endif
