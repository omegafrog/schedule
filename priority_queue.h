#ifndef __READY_QUEUE_H__
#include "process.h"


typedef struct que_ {
	process* processData;
	struct que_* next;
} priority_queue;

process* pop(priority_queue** head);
void push(priority_queue** head, process* );  
process* selectProcessFromQue(priority_queue** q1, priority_queue** q2, priority_queue** q3, priority_queue** q4);
void insertProcessQue(priority_queue** q1, priority_queue** q2, priority_queue** q3, priority_queue** q4, process* processData);



#endif