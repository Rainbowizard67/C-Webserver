#include "../headers/hashTable.h"

static size_t hash_function(char* key, int size) {
    size_t hash = 0;
    while(*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % size;
}

hashTable_t* create_table(int size) {
    hashTable_t* tb = (hashTable_t*)(sizeof(hashTable_t));
    if(!tb) return NULL;
    memset(tb->buckets, 0, sizeof(tb->buckets));
    return tb;
}

LNode_t* create_node(char* key, char* val) {
    LNode_t* newNode = (LNode_t*)malloc(sizeof(LNode_t));
    if(!newNode) return NULL;
    newNode->key = strdup(key);
    newNode->value = strdup(val);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insert(hashTable_t* tb, char* key, char* val) {
    size_t index = hash_function(key);
}

void del(hashTable_t* tb, char* key) {

}

char* search(hashTable_t* tb, char* key) {

}

void free_node(LNode_t* node) {
    free(node->key);
    free(node->value);
    free(node);
}

void free_table(hashTable_t* tb, int size) {
    for(int i=0; i<size; i++) {
        LNode_t* node = tb->buckets[i];
        while(node) {
            LNode_t* temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(tb);
}