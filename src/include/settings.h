#ifndef NETDATA_H
#define NETDATA_H

#include <cyaml/cyaml.h>
#include "scurry_utils.h"
#include "project_headers.h"

#define MAX_FILEPATH_SIZE 256

#define HT_SIZE 7

hashTable_t* main_settings(char* fp);
void* get_value(hashTable_t* ht, char* key);
void free_settings(hashTable_t* ht);

#endif