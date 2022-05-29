#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void initQueue(ReadyQueue *queue)
{
    queue->front = -1;
    queue->rear = -1;
    queue->data = (process **)malloc(sizeof(process *) * MAX_READY_QUEUE_SIZE);
}
void push(ReadyQueue *queue, process *newProcess)
{
    if (!isFull(queue))
    {
        queue->data[++queue->front] = newProcess;
    }
    else
    {
        printf("queue is full\n");
    }
}
process *pop(ReadyQueue *queue)
{
    if (!isEmpty(queue))
    {
        return queue->data[++queue->rear];
    }
    else
    {
        printf("queue is empty\n");
        return NULL;
    }
}
process *peek(ReadyQueue *queue)
{
    if (!isEmpty(queue))
    {
        return queue->data[queue->rear];
    }
    else
    {
        printf("queue is emtpy\n");
    }
}
bool isEmpty(ReadyQueue *Queue)
{
    return (Queue->front <= Queue->rear) ? true : false;
}
bool isFull(ReadyQueue *queue)
{
    return (queue->front == MAX_READY_QUEUE_SIZE - 1) ? true : false;
}