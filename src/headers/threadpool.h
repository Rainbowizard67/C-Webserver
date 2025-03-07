#ifndef TPOOL_H
#define TPOOL_H

#include "project_headers.h"

//Thread function to be passed, has void pointer for any data types
typedef void (*thread_func_t)(void* arg);

//structures

//This is our singly linked list of thread functions for the queue
typedef struct tpool_work {
    thread_func_t func;
    void* arg;
    tpool_work* next;
}tpool_work;
typedef struct tpool_work tpool_work_t;

//This is the pool queue structure
typedef struct tpool {
    tpool_work_t* work_first;
    tpool_work_t* work_last;
    pthread_mutex_t work_mutex;
    pthread_cond_t work_cond;
    pthread_cond_t working_cond;
    size_t working_cnt;
    size_t thread_cnt;
    bool stop;
}tpool;
typedef struct tpool tpool_t;

//end structures


//function prototypes
tpool_t* tpool_create(size_t num);
void tpool_destroy(tpool_t* tm);

bool tpool_add_work(tpool_t* tm, thread_func_t func, void* arg);
void tpool_wait(tpool_t* tm);
//end function prototypes

#endif