#ifndef __READY_QUEUE_H__
#include "process.h"
#include <stdbool.h>

#define __READY_QUEUE_H__
#define MAX_READY_QUEUE_SIZE 100
typedef struct ReadyQueue
{
    int front;
    int rear;
    process **data;
} ReadyQueue;

void initQueue(ReadyQueue *queue);
void push(ReadyQueue *queue, process *newProcess);
process *pop(ReadyQueue *queue);
process *peek(ReadyQueue *queue);
bool isEmpty(ReadyQueue *ReadyQueue);
bool isFull(ReadyQueue *ReadyQueue);
#endif