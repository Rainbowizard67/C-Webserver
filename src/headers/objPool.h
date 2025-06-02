#ifndef OBJ_POOL_H
#define OBJ_POOL_H

#include "project_headers.h"

typedef struct object_pool {
    client_connection_t* objects;
    int size;
    int capacity;
    int* available;
}object_pool_t;

//Start function prototypes
object_pool_t* create_pool(int cap);
client_connection_t* borrow_object(object_pool_t* pool);
void return_object(object_pool_t* pool, client_connection_t* object);
void destroy_pool(object_pool_t* pool);
//End function prototypes


#endif