#include "process.h"
#include "result.h"

#ifndef __IO_H__

#define __IO_H__
#define MAX_PROCESS_COUNT 100

int getProcessInput(process *processList, int *processCount);
int getProcessInputFile(char *fileName, process *processList, int *processCount);
void show_round_robin(process *processList, result *resultList, int size);
void show_priority(result *schedulingList, int processCount);

#endif