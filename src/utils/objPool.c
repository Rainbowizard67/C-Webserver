#include "../include/objPool.h"

/*
Function that inits the pool with the base capacity.
Argument input is int cap, returns object_pool_t structure.
*/
object_pool_t* create_pool(int cap) {
    object_pool_t* pool = (object_pool_t*)malloc(sizeof(object_pool_t));
    pool->size = 0;
    pool->capacity = cap;
    pool->objects = (client_connection_t*)malloc(sizeof(client_connection_t) * cap);
    pool->available = (int*)malloc(sizeof(int) * cap);

    for(int i=0; i<cap; i++) {
        pool->available[i] = true;
    }
    return pool;
}


/*
Static function that resizes the pool if it reaches general capacity.
Argument input is object_pool_t structure, returns void.
*/
static void resize_pool(object_pool_t* pool) {
    int old_capacity = pool->capacity;  
    int new_capacity = old_capacity + 2;

    pool->objects = realloc(pool->objects, sizeof(client_connection_t) * new_capacity);
    pool->available = realloc(pool->available, sizeof(int) * new_capacity);
    
    for(int i=old_capacity; i<pool->capacity; i++) {
        pool->available[i] = true;
    }

    pool->capacity = new_capacity;
}

/*
Function that borrows an object to be used else where.
Argument input is object_pool_t structure, returns client_connection_t structure.
*/
client_connection_t* borrow_object(object_pool_t* pool) {
    if(pool->size == pool->capacity) {
        resize_pool(pool);
    }
    for(int i=0; i<pool->capacity; i++) {
        if(pool->available[i] == true) {
            pool->available[i] = false;
            pool->size++;
            client_connection_t* obj = &pool->objects[i];
            memset(obj, 0, sizeof(client_connection_t));
            return obj;
        }
    }
    return NULL;   
}

/*
Function that returns an object back to the memory pool after using.
Argument inputs are object_pool_t structure and client_connection_t structure, returns void.
*/
void return_object(object_pool_t* pool, client_connection_t* object) {
    int index = object - pool->objects;
    if(index >= 0 && index < pool->capacity) {
        pool->available[index] = true;
        pool->size--;
    }
}

/*
Function that frees the entire memory pool and objects.
Argument input is object_pool_t structure, return void.
*/
void destroy_pool(object_pool_t* pool) {
    free(pool->objects);
    free(pool->available);
    free(pool);
}