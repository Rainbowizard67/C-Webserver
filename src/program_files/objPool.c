#include "../headers/objPool.h"

//Init pool with base capacity
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

//Resizes pool if it reaches general capacity 
static void resize_pool(object_pool_t* pool) {
    int new_capacity = pool->capacity + 2;
    pool->objects = realloc(pool->objects, sizeof(client_connection_t) * new_capacity);
    pool->available = realloc(pool->available, sizeof(int) * new_capacity);
    
    for(int i=pool->size; i<pool->capacity; i++) {
        pool->available[i] = true;
    }
}

//Borrows an object to be used else where
client_connection_t* borrow_object(object_pool_t* pool) {
    if(pool->size == pool->capacity) {
        resize_pool(pool);
    }
    for(int i=0; i<pool->capacity; i++) {
        if(pool->available[i] == true) {
            pool->available[i] = false;
            pool->size++;
            return &pool->objects[i];
        }
    }
    return NULL;   
}

//Returns object back to the pool after using it
void return_object(object_pool_t* pool, client_connection_t* object) {
    int index = object - pool->objects;
    if(index >= 0 && index < pool->capacity) {
        pool->available[index] = true;
        pool->size--;
    }
}

//Frees entire pool and objects
void destroy_pool(object_pool_t* pool) {
    free(pool->objects);
    free(pool->available);
    free(pool);
}