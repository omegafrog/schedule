#include <stdio.h>
#include <stdlib.h>
#include "fcfs_queue.h"

void init_queue(QueueType* q) {	//����ť �ʱ�ȭ
	q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item) {	//����ť ����
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {	//����ť ����
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int is_empty(QueueType* q) {	//���� ���� ����
	return (q->front == q->rear);
}
