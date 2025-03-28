#ifndef LRU_CACHE
#define LRU_CACHE

#include "project_headers.h"
#include "hashMap.h"

#define HASH_SIZE 1024 //1KB

//hash table that is the LRU cache
typedef struct LRUCache {
    int capacity; //max size of cache
    int size; //current size of cache
    LNode_t** hastTable;
    LNode_t* head;
    LNode_t* tail;
} LRUCache;

//function prototypes
size_t hash();
LNode_t* createNode();
LRUCache* createCache();
void moveToHead();
void removeTail();
int get();
int put();

#endif