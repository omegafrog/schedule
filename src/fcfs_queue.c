#include <stdio.h>
#include <stdlib.h>
#include "fcfs_queue.h"

void init_queue(QueueType *q)
{ //레디큐 초기화 함수
	q->front = q->rear = 0;
}

void enqueue(QueueType *q, element item)
{ //레디큐 삽입 함수
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{ //레디큐 삭제 함수
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int is_empty(QueueType *q)
{ //공백 상태 검출 함수
	return (q->front == q->rear);
}
