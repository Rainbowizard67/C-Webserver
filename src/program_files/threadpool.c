#include "../headers/threadpool.h"

//function for adding work node to the linked list
static tpool_work_t* tpool_work_create(thread_func_t func, void* arg) {
    tpool_work_t* work;

    if(func==NULL) {
        return NULL;
    }

    work = malloc(sizeof(*work));
    work->func = func;
    work->arg = arg;
    work->next = NULL;
    
    return work;
}

//function for freeing work node from the linked list
static void tpool_work_destroy(tpool_work_t* work) {
    if(work==NULL) {
        return;
    }
    free(work);
}

//function for returning specific work objects from the list
static tpool_work_t* tpool_work_get(tpool_t* tm) {
    tpool_work_t* work;

    if(tm==NULL) {
        return NULL;
    }

    work = tm->work_first;
    if(work==NULL) {
        return NULL;
    }

    if(work->next==NULL) {
        tm->work_first = NULL;
        tm->work_last = NULL;
    }
    else {
        tm->work_first = work->next;
    }

    return work;
}

//main worker function that waits for 
static void* tpool_worker(void* arg) {
    tpool_t* tm = arg;
    tpool_work_t* work;

    while(true) {
        pthread_mutex_lock(&(tm->work_mutex));

        while(tm->work_first == NULL && !tm->stop) {
            pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));
        }
        if(tm->stop) {break;}

        work = tpool_work_get(tm);
        tm->working_cnt++;
        pthread_mutex_unlock(&(tm->work_mutex));

        if(work!=NULL) {
            work->func(work->arg);
            tpool_work_destroy(work);
        }

        pthread_mutex_lock(&(tm->work_mutex));
        tm->working_cnt--;
        if(!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL) {
            pthread_cond_signal(&(tm->working_cond));
        }
        pthread_mutex_unlock(&(tm->work_mutex));
    }

    tm->thread_cnt--;
    pthread_cond_signal(&(tm->working_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    return NULL;
}

tpool_t* tpool_create(size_t num) {
    tpool_t* tm;
    pthread_t thread;
    size_t i;

    if(num==0) {
        num=2;
    }
    tm=calloc(1, sizeof(*tm));
    tm->thread_cnt = num;

    pthread_mutex_init(&(tm->work_mutex), NULL);
    pthread_cond_init(&(tm->work_cond), NULL);
    pthread_cond_init(&(tm->working_cond), NULL);

    tm->work_first = NULL;
    tm->work_last = NULL;

    for(i=0; i<num; i++) {
        pthread_create(&thread, NULL, tpool_worker, tm);
        pthread_detach(thread);
    }

    return tm;
}