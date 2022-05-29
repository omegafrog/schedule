#ifndef __PRIOR_SCHEDULING_H__
#define __PRIOR_SCHEDULING_H__

#include "process.h"
#include "result.h"

void priority_scheduling(process *processList, unsigned int size, unsigned int quantTime, result *resultList);
void completeTask(result *resultList, process *completeProcess);
#endif
