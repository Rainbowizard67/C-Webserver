#ifndef LRU_CACHE
#define LRU_CACHE

#include "project_headers.h"
#include "hashTable.h"

#define HASH_SIZE 1024 //1KB

//hash table that is the LRU cache
typedef struct LRUCache {
    int capacity; //max size of cache
    int size; //current size of cache
    LNode_t** hastTable;
    LNode_t* head;
    LNode_t* tail;
}LRUCache_t;

//function prototypes

//end function prototypes

#endif