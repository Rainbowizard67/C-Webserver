#include "../headers/hashTable.h"

//TODO, see what other hash_functions we can use and if we can dynamically choose which one we want to implement

/*
Hash static function that converts the key into hash value.
Argument inputs are char* key and int size, return size_t.
*/
static size_t hash_function(char* key, int size) {
    size_t hash = 0;
    while(*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % size;
}

/*
Function that creates the main hash table.
Argument input is int size, returns hashTable_t structure.
*/
hashTable_t* create_table(int size) {
    hashTable_t* tb = (hashTable_t*)malloc(sizeof(hashTable_t));
    if(!tb) return NULL;
    tb->buckets = (LNode_t**)malloc(sizeof(LNode_t*) * size);
    if(!tb->buckets) {
        free(tb);
        return NULL;
    }
    memset(tb->buckets, 0, sizeof(LNode_t*) * size);
    tb->capacity = size;
    return tb;
}

/*
Static function that creates nodes for insert function.
Argument inputs are char* key, void* val, and size_t val_size, returns LNode_t structure.
*/
static LNode_t* create_node(char* key, void* val, size_t val_size) {
    LNode_t* newNode = (LNode_t*)malloc(sizeof(LNode_t));
    if(!newNode) return NULL;
    newNode->key = strdup(key);
    newNode->value = malloc(val_size);
    if(!newNode->value) {
        free(newNode->key);
        free(newNode);
        return NULL;
    }
    memcpy(newNode->value, val, val_size);
    newNode->value_size = val_size;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/*
Function that inserts a node into the hashtable.
Argument inputs are hashTable_t structure, char* key, void* val, and size_t val_size, returns void.
*/
void insert(hashTable_t* tb, char* key, void* val, size_t val_size) {
    size_t index = hash_function(key, tb->capacity);
    LNode_t* node = tb->buckets[index];

    while(node) {
        if(strcmp(node->key, key) == 0) {
            free(node->value);
            node->value = malloc(val_size);
            memcpy(node->value, val, val_size);
            node->value_size = val_size;
            return;
        }
        node = node->next;
    }
    
    LNode_t* newNode = create_node(key, val, val_size);
    if(!newNode) return;
    newNode->next = tb->buckets[index];
    if(tb->buckets[index]) {
        tb->buckets[index]->prev = newNode;
    }
    tb->buckets[index] = newNode;
}

/*
Static function that frees the node and its dynamically allocated members.
Argument input is LNode_t structure, returns void.
*/
static void free_node(LNode_t* node) {
    free(node->key);
    free(node->value);
    free(node);
}

/*
Function that deletes a key:value pair from the hashtable.
Argument inputs are hashTable_t structure and char* key, returns void.
*/
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

/*
Function that searches and returns value based on the key.
Argument inputs are hashTable_t structure and char* key, returns void pointer.
*/
void* search(hashTable_t* tb, char* key) {
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

/*
Function that frees all nodes and hashtable structure.
Argument input is hashTable_t structure, returns void.
*/
void free_table(hashTable_t* tb) {
    for(int i=0; i<tb->capacity; i++) {
        LNode_t* node = tb->buckets[i];
        while(node) {
            LNode_t* temp = node;
            node = node->next;
            free_node(temp);
        }
    }
    free(tb->buckets);
    free(tb);
}