#ifndef __PRIORITY_QUEUE_H__
#include "process.h"

#define __PRIORITY_QUEUE_H__

typedef struct que_
{
	process *processData;
	struct que_ *next;
} priority_queue;

process *priority_pop(priority_queue **head);
void priority_push(priority_queue **head, process *);
process *selectProcessFromQue(priority_queue **q1, priority_queue **q2, priority_queue **q3, priority_queue **q4);
void insertProcessQue(priority_queue **q1, priority_queue **q2, priority_queue **q3, priority_queue **q4, process *processData);

#endif
