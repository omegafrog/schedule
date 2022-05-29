#ifndef __FCFS_QUEUE_H__
#define __FCFC_QUEUE_H__

#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct {	//큐 타입(원형 큐)
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;


void enqueue(QueueType* q, element item);
void init_queue(QueueType* q);
element dequeue(QueueType* q);
int is_empty(QueueType* q);
#endif // !__FCFS_QUEUE_H__
