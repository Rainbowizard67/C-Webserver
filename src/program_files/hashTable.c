#include "../headers/hashTable.h"

//TODO, test to make sure if we need to create a compatability layer to make sure any data can be inputted using the void pointer not just ints or strings but everything
//TODO, see what other hash_functions we can use and if we can dynamically choose which one we want to implement
static size_t hash_function(char* key, int size) {
    size_t hash = 0;
    while(*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % size;
}

hashTable_t* create_table(int size) {
    hashTable_t* tb = (hashTable_t*)malloc(sizeof(hashTable_t));
    if(!tb) return NULL;
    memset(tb->buckets, 0, size);
    tb->capacity = size;
    return tb;
}

static LNode_t* create_node(char* key, char* val) {
    LNode_t* newNode = (LNode_t*)malloc(sizeof(LNode_t));
    if(!newNode) return NULL;
    newNode->key = strdup(key);
    newNode->value = strdup(val);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insert(hashTable_t* tb, char* key, char* val) {
    size_t index = hash_function(key, tb->capacity);
    LNode_t* newNode = create_node(key, val);
    if(!newNode) return;
    newNode->next = tb->buckets[index];
    if(tb->buckets[index]) {
        tb->buckets[index]->prev = newNode;
    }
    tb->buckets[index] = newNode;
}

static void free_node(LNode_t* node) {
    free(node->key);
    free(node->value);
    free(node);
}

void del(hashTable_t* tb, char* key) {
    size_t index = hash_function(key, tb->capacity);
    LNode_t* node = tb->buckets[index];
    while(node) {
        if(strcmp(node->key, key) == 0) {
            if(node->prev) {
                node->prev->next = node->next;
            }
            else {
                tb->buckets[index] = node->next;
            }
            if(node->next) {
                node->next->prev = node->prev;
            }
            free_node(node);
            return;
        }
        node = node->next;
    }
}

char* search(hashTable_t* tb, char* key) {
    size_t index = hash_function(key, tb->capacity);
    LNode_t* node = tb->buckets[index];
    while(node) {
        if(strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void free_table(hashTable_t* tb) {
    for(int i=0; i<tb->capacity; i++) {
        LNode_t* node = tb->buckets[i];
        while(node) {
            LNode_t* temp = node;
            node = node->next;
            free_node(temp);
        }
    }
    free(tb);
}