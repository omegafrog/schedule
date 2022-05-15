
#ifndef __RESULT_H__

#define __RESULT_H__

typedef struct _result
{
	int process_id;
	char process_qId[10];
	int priority;
	int computing_time;
	int turnaround_time;

} Result;

#endif