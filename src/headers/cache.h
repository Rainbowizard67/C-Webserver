#ifndef LRU_CACHE
#define LRU_CACHE

#include "project_headers.h"

//1kb
#define HASH_SIZE 1024

//doublely linked-list
typedef struct dNode {
    char* key;
    void* value;
    dNode* prev;
    dNode* next;
} dNode;

//hash table that is the LRU cache
typedef struct LRUCache {
    int capacity; //max size of cache
    int size; //current size of cache
    dNode** hastTable;
    dNode* head;
    dNode* tail;
} LRUCache;

//function prototypes
size_t hash();
dNode* createNode();
LRUCache* createCache();
void moveToHead();
void removeTail();
int get();
int put();

#endif