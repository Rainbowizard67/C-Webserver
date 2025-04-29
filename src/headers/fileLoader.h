#ifndef FILE_LOADER
#define FILE_LOADER

#include "project_headers.h"
#include <sys/stat.h>

//struct
typedef struct file_data {
    int size;
    void* data;
}file_data_t;
//end struct

//function prototypes
void file_free(file_data_t* filedata);
file_data_t* file_load(char* filename);
//end function prototypes

#endif