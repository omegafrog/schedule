#ifndef __PRIOR_SCHEDULING_H__
#define __PRIOR_SCHEDULING_H__

#include "process.h"
#include "result.h"

void priority_scheduling(process* processList, unsigned int size, unsigned int quantTime, Result* resultList);
void completeTask(Result* resultList, process* completeProcess);
#endif
