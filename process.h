#ifndef __PROCESS_H__

#define __PROCESS_H__


typedef struct _process
{
	int type;
	int process_id;
	int priority;
	int computing_time;
	int remain_computing_time;
	int start_time;
	int end_time;
} process;

#endif