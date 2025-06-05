#include "../include/cache.h"

/*
Static function creates node for cache.
Argument input is char* key and char* val, returns LRU_Node_t structure.
*/
static LRU_Node_t* create_lru_node(char* key, char* val) {
    LRU_Node_t* node = (LRU_Node_t*)malloc(sizeof(LRU_Node_t));
    if(!node) return NULL;
    node->key = strdup(key);
    node->value = strdup(val);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

/*
Function that creates the LRU cache.
Argument input is int cap, returns LRUCache_t structure.
*/
LRUCache_t* init_cache(int cap) {
    LRUCache_t* cache = (LRUCache_t*)malloc(sizeof(LRUCache_t));
    if(!cache) return NULL;

    cache->capacity = cap;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->map = create_table(cap);

    return cache;
}

/*
Static function that moves node to the front of the node (most recently used).
Argument inputs are LRUCache_t structure and LRU_Node_t structure, returns void.
*/
static void move_front(LRUCache_t* cache, LRU_Node_t* node) {
    if(cache->head == node) return;

    if(node->prev) node->prev->next = node->next;
    if(node->next) node->next->prev = node->prev;
    if(cache->tail == node) cache->tail = node->prev;

    node->next = cache->head;
    node->prev = NULL;
    if(cache->head) cache->head->prev = node;
    cache->head = node;

    if(!cache->tail) cache->tail = node;
}

/*
Static function that removes the least recently used node.
Argument input is LRUCache_t structure, returns void.
*/
static void evict_lru(LRUCache_t* cache) {
    if(!cache->tail) return;

    LRU_Node_t* node_to_remove = cache->tail;
    del(cache->map, node_to_remove->key);

    if(node_to_remove->prev) {
        node_to_remove->prev->next = NULL;
    }
    else {
        cache->head = NULL;
    }
    cache->tail = node_to_remove->prev;

    free(node_to_remove->key);
    free(node_to_remove->value);
    free(node_to_remove);

    cache->size--;
}

/*
Function that inserts a key-value pair into the LRU cache.
Argument inputs are LRUCache_t structure, char* key, and char* value, returns void.
*/
void put(LRUCache_t* cache, char* key, char* value) {
    LRU_Node_t* node = (LRU_Node_t*)search(cache->map, key);

    if(node) {
        free(node->value);
        node->value = strdup(value);
        move_front(cache, node);
    }
    else {
        LRU_Node_t* newNode = create_lru_node(key, value);
        if(!newNode) return;
 
        insert(cache->map, key, newNode->value, sizeof(newNode->value));

        newNode->next = cache->head;
        if(cache->head) cache->head->prev = newNode;
        cache->head = newNode;

        if(!cache->tail) cache->tail = newNode;

        cache->size++;

        if(cache->size > cache->capacity) {
            evict_lru(cache);
        }
    }
}

/*
Function that gets a value from the cache.
Argument inputs are LRUCache_t structure and char* key, returns char pointer.
*/
char* get(LRUCache_t* cache, char* key) {
    LRU_Node_t* node = (LRU_Node_t*)search(cache->map, key);
    if(!node) return NULL;

    move_front(cache, node);
    return node->value;
}

/*
Function that frees the LRU cache from memory.
Argument input is LRUCache_t structure, returns void.
*/
void free_LRU_cache(LRUCache_t* cache) {
    LRU_Node_t* current = cache->head;
    while(current) {
        LRU_Node_t* temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    free_table(cache->map);
    free(cache);
}
