#ifndef PREPROCESS_HANDLECLIENT
#define PREPROCESS_HANDLECLIENT

#include "../headers/project_headers.h"
#include "../headers/fileLoader.h"
#include "../headers/hashTable.h"

#define MAX_CACHE_SIZE 5
#define MAX_METHOD_SIZE 10

struct timeval timeout;

typedef struct parse_data {
    bool check;
    char method[MAX_METHOD_SIZE];
}parse_data_t;

void http_client_handler(client_request_t* client);

#endif
