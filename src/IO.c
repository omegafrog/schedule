#include <stdio.h>
#include <unistd.h>

#include "IO.h"

int getProcessInput(process *processList, int *processCount)
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
        if (tmpProcess.type == 0)
            (*processCount)++;
        count++;
        scanf("%d %d %d", &tmpProcess.process_id, &tmpProcess.priority, &tmpProcess.computing_time);
        tmpProcess.remain_computing_time = tmpProcess.computing_time;
        tmpProcess.start_time = -1;
        tmpProcess.end_time = 0;
        processList[i] = tmpProcess;
        getchar();
    }
    return count;
}

int getProcessInputFile(char *fileName, process *processList, int *processCount)
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
    printf("%s\n", path);
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
                if (processList[idx].type == 0)
                    (*processCount)++;
                processList[idx].process_id = output[1];
                processList[idx].priority = output[2];
                processList[idx].start_time = -1;
                processList[idx].end_time = 0;
                processList[idx].remain_computing_time = output[3];
                processList[idx++].computing_time = output[3];

                i = 0;
            }
        } while (c != -1);
    }
    return count;
}

void show_round_robin(process *processList, result *resultList, int size)
{

    printf("---------------------Schedulling Output ------------------------------\n");
    int sum_turnaround_time = 0;
    int processCount = size;
    printf("Process_id\t priority\t computing_time\t turn_around_time\n");

    for (int i = 0; i < size; ++i)
    {
        printf("%d\t\t %d\t\t %d\t\t %d\n", resultList[i].process_id, resultList[i].priority, resultList[i].computing_time, resultList[i].turnaround_time);
        sum_turnaround_time += resultList[i].turnaround_time;
    }
    printf("average turnaround_time : %d \n", sum_turnaround_time / processCount);
}

void show_priority(result *schedulingList, int processCount)
{
    printf("---------------------Schedulling Output ------------------------------\n");
    int sum_turnaround_time = 0;
    printf("Process_id\t Queue_id \t\t priority\t computing_time\t turn_around_time\n");

    for (int i = 0; i < processCount; i++)
    {

        printf("%d\t\t %-9s\t\t %d\t\t %d\t\t %d\n",
               schedulingList[i].process_id, schedulingList[i].process_qId, schedulingList[i].priority, schedulingList[i].computing_time, schedulingList[i].turnaround_time);
        sum_turnaround_time += schedulingList[i].turnaround_time;
    }

    printf("average turnaround_time : %d \n", sum_turnaround_time / processCount);
}