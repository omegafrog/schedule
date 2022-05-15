#include <stdio.h>
#include <unistd.h>

#include "IO.h"

int getProcessInput(process *processList)
{
    printf("type\t pid\t priority\t computing-time\n");
    int count = 0;
    for (int i = 0; i < MAX_PROCESS_COUNT; ++i)
    {
        process tmpProcess;
        scanf("%d", &tmpProcess.type);
        if (tmpProcess.type == -1)
        {
            return count;
        }
        count++;
        scanf("%d %d %d", &tmpProcess.process_id, &tmpProcess.priority, &tmpProcess.computing_time);
        tmpProcess.startClockTime = -1;
        tmpProcess.endClockTime = 0;
        processList[i] = tmpProcess;
        getchar();
    }
    return count;
}

int getProcessInputFile(char *fileName, process *processList)
{
    // num of process
    // open file
    // absolute file path
    int count = 0;
    FILE *fptr;
    char path[200];

    // get current work directory
    getcwd(path, 200);
    int i = 0;
    while (path[i] != '\0')
    {
        i++;
    }
    path[i++] = '/';
    // add file name after current working directory
    int j = 0;
    while (fileName[j] != '\0')
    {
        path[i++] = fileName[j++];
    }
    path[i] = '\0';

    // open file
    fptr = fopen(path, "r");
    if (fptr == NULL)
    {
        printf("error");
        return -1;
    }
    else
    {
        int idx = 0;
        int i = 0;
        int c;
        do
        {
            int output[4];
            fscanf(fptr, "%d ", &c);
            output[i++] = c;
            if (i == 4)
            {
                count++;
                processList[idx].type = output[0];
                processList[idx].process_id = output[1];
                processList[idx].priority = output[2];
                processList[idx].startClockTime = -1;
                processList[idx].endClockTime = 0;
                processList[idx++].computing_time = output[3];
                i = 0;
            }
        } while (c != -1);
    }
    return count;
}

void show(process *processList, result *resultList, int size)
{
    printf("Process_id\t priority\t computing_time\t turn_around_time\n");

    for (int i = 0; i < size; ++i)
    {
        if (resultList[i].process_id == 0)
            continue;
        printf("%d\t\t %d\t\t %d\t\t %d\n", resultList[i].process_id, resultList[i].priority, processList[i].computing_time, resultList[i].turnaround_time);
    }
}