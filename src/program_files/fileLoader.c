#include "../headers/fileLoader.h"
/*
This function loads the file data into memory for use.
Input argument is a char* pointer filename, returns file_data_t structure.
*/
file_data_t* file_load(char* filename) {
    char* buffer, *ptr;

    struct stat buf;
    int bytes_read, bytes_remaining, total_bytes = 0;

    //Getting the file size
    if(stat(filename, &buf) == -1) {
        return NULL;
    }

    //Making sure it is a regular file
    if(!(buf.st_mode & __S_IFREG)) return NULL;

    FILE* fp = fopen(filename, "rb");

    if(fp == NULL) return NULL;

    //Allocate memory for the file
    bytes_remaining = buf.st_size;
    ptr = buffer = malloc(bytes_remaining);

    if(buffer == NULL) return NULL;

    //Reading in entire file into memory
    while(bytes_read = fread(ptr, 1, bytes_remaining, fp), bytes_read != 0 && bytes_remaining > 0) {
        if(bytes_read == -1) {
            free(buffer);
            return NULL;
        }

        bytes_remaining -= bytes_read;
        ptr += bytes_read;
        total_bytes += bytes_read;
    }

    file_data_t* filedata = malloc(sizeof(file_data_t));

    if(filedata == NULL) {
        free(buffer);
        return NULL;
    }

    filedata->data = buffer;
    filedata->size = total_bytes;

    return filedata;    
}

/*
This function frees the file_data_t structure from memory.
Input argument is the file_data_t structure, returns void.
*/
void file_free(file_data_t* filedata) {
    free(filedata->data);
    free(filedata);
}