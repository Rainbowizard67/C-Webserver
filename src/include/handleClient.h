#ifndef PREPROCESS_HANDLECLIENT
#define PREPROCESS_HANDLECLIENT

#include "project_headers.h"
#include "fileLoader.h"
#include "cache.h"

#define MAX_CACHE_SIZE 5
#define MAX_METHOD_SIZE 10

struct timeval timeout;

char* d_web_path;
char* d_config_path;

typedef struct parse_data {
    bool check;
    char method[MAX_METHOD_SIZE];
}parse_data_t;

void http_client_handler(client_connection_t* client);

#endif
