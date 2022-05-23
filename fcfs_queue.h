#ifndef __FCFS_QUEUE_H__
#define __FCFC_QUEUE_H__


typedef int element;
typedef struct {	//ť Ÿ��(���� ť)
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;


void enqueue(QueueType* q, element item);
void init_queue(QueueType* q);
element dequeue(QueueType* q);
int is_empty(QueueType* q);
#endif // !__FCFS_QUEUE_H__
