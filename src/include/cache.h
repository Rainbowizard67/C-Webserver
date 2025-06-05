#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "project_headers.h"
#include "hashTable.h"

//structures
//LRU_Node
typedef struct LRU_Node {
    char* key;
    char* value;
    struct LRU_Node* prev;
    struct LRU_Node* next;
}LRU_Node_t;
//end LRU_Node

//LRU_Cache
typedef struct LRUCache {
    int capacity; //max size of cache
    int size; //current size of cache
    hashTable_t* map;
    LRU_Node_t* head;
    LRU_Node_t* tail;
}LRUCache_t;
//end LRU_Cache
//end structures

//function prototypes
LRUCache_t* init_cache(int cap);
void put(LRUCache_t* cache, char* key, char* value);
char* get(LRUCache_t* cache, char* key);
void free_LRU_cache(LRUCache_t* cache);
//end function prototypes

#endif