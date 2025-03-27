#ifndef HASH_MAP
#define HASH_MAP

#include "project_headers.h"

//structs
typedef struct LNode {
    char* key;
    char* value;
    struct LNode* next;
}LNode_t;

typedef struct hashMap {
    int num_elements;
    int capacity;
    LNode_t arr;
}hashMap_t;
//end structs

#endif