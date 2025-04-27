#ifndef NETDATA_H
#define NETDATA_H

#include <cyaml/cyaml.h>
#include "hashTable.h"
#include "project_headers.h"

#define MAX_FILEPATH_SIZE 256

hashTable_t* settings(void);
void* get_value(hashTable_t* ht, char* key);

#endif