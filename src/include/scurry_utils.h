#ifdef SCURRY_UTILS_H
#define SCURRY_UTILS_H

#include "project_headers.h"
#include <sys/stat.h>

/*=============================
| Start Async Threadpool Util |
==============================*/

//Thread function to be passed, has void pointer for any data types
typedef void (*thread_func_t)(void* arg);

//start structures

//This is our singly linked list of thread functions for the queue
typedef struct tpool_work tpool_work;
typedef struct tpool_work {
    thread_func_t func;
    void* arg;
    tpool_work* next;
}tpool_work;
typedef struct tpool_work tpool_work_t;

typedef struct tpool {
    tpool_work_t* work_first;
    tpool_work_t* work_last;
    pthread_mutex_t work_mutex;
    pthread_cond_t work_cond;
    pthread_cond_t working_cond;
    size_t working_cnt;
    size_t thread_cnt;
    bool stop;
}tpool;
typedef struct tpool tpool_t;

tpool_t* tpool_create(size_t num);
void tpool_destroy(tpool_t* tm);

bool tpool_add_work(tpool_t* tm, thread_func_t func, void* arg);
void tpool_wait(tpool_t* tm);

/*===========================
| End Async Threadpool Util |
=============================
|   Start Object Pool Util  |
============================*/

typedef struct object_pool {
    client_connection_t* objects;
    int size;
    int capacity;
    int* available;
}object_pool_t;

object_pool_t* create_pool(int cap);
client_connection_t* borrow_object(object_pool_t* pool);
void return_object(object_pool_t* pool, client_connection_t* object);
void destroy_pool(object_pool_t* pool);

/*=======================
| End Object Pool Util  |
=========================
| Start Hash Table Util |
========================*/

typedef struct LNode {
    char* key;
    void* value;
    size_t value_size;
    struct LNode* next;
    struct LNode* prev;
}LNode_t;

typedef struct hashTable {
    int capacity;
    LNode_t** buckets;
}hashTable_t;

hashTable_t* create_table(int size);
void insert(hashTable_t* tb, char* key, void* val, size_t val_size);
void del(hashTable_t* tb, char* key);
void* search(hashTable_t* tb, char* key);
void free_table(hashTable_t* tb);

/*=======================
| End Hash Table Util   |
=========================
| Start LRU Cache Util  |
========================*/

typedef struct LRU_Node {
    char* key;
    char* value;
    struct LRU_Node* prev;
    struct LRU_Node* next;
}LRU_Node_t;

typedef struct LRUCache {
    int capacity; //max size of cache
    int size; //current size of cache
    hashTable_t* map;
    LRU_Node_t* head;
    LRU_Node_t* tail;
}LRUCache_t;

LRUCache_t* init_cache(int cap);
void put(LRUCache_t* cache, char* key, char* value);
char* get(LRUCache_t* cache, char* key);
void free_LRU_cache(LRUCache_t* cache);

/*========================
|   End LRU Cache Util   |
==========================
| Start File Loader Util |
=========================*/

//struct
typedef struct file_data_t {
    int size;
    void* data;
}file_data_t;
//end struct

//function prototypes
void file_free(file_data_t* filedata);
file_data_t* file_load(char* filename);
//end function prototypes

/*======================
| End File Loader Util |
=======================*/

#endif