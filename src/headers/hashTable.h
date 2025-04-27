#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "project_headers.h"

#define HT_SIZE 7

//structs
typedef struct LNode {
    char* key;
    void* value;
    struct LNode* next;
    struct LNode* prev;
}LNode_t;

typedef struct hashTable {
    int capacity;
    LNode_t** buckets;
}hashTable_t;
//end structs

//function prototypes
hashTable_t* create_table(int size);
void insert(hashTable_t* tb, char* key, void* val);
void del(hashTable_t* tb, char* key);
void* search(hashTable_t* tb, char* key);
void free_table(hashTable_t* tb);
//end function prototypes

#endif