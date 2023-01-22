#ifndef SATGE_H
#define SATGE_H
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


#define MAX_TEMP 30
typedef Node * (*task_func)(int * h,Node  *);
typedef struct stage{
    pthread_t thread;
    bool isActive;
    Queue* sourseQu;
    Queue* destQu;
    task_func func;
    struct stage * next_satge;
}stage;

typedef  struct task{
    stage * my_stage;
    int * my_status;
   // node * my_current_node;

} task_t;
stage * init_stage(task_func func ,Queue * destq,Queue * sourcq,stage*);
void * main_satge(void * arg);
#endif // SATGE_H
