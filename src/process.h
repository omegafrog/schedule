#ifndef __PROCESS_H__

#define __PROCESS_H__
typedef struct _perocess
{
    int type;
    int process_id;
    int priority;
    int computing_time;
    int startClockTime;
    int endClockTime;
} process;
#endif