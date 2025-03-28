#ifndef HASH_MAP
#define HASH_MAP

#include "project_headers.h"

//structs
typedef struct LNode {
    char* key;
    void* value;
    struct LNode* next;
    struct LNode* prev;
}LNode_t;

typedef struct hashTable {
    int num_elements;
    int capacity;
    struct LNode_t* buckets;
}hashTable_t;
//end structs

//function prototypes

//end function prototypes

#endif