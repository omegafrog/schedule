#include "process.h"
#include "result.h"

#ifndef __IO_H__

#define __IO_H__
#define MAX_PROCESS_COUNT 100

int getProcessInput(process *processList);
int getProcessInputFile(char *fileName, process *processList);
void show(process *processList, result *resultList, int size);

#endif