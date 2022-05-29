#include <stdio.h>
#include <stdlib.h>

#include "scheduling.h"
#include "process.h"
#include "result.h"
#include "IO.h"
#include "priority_scheduling.h"
#include "fcfs_scheduling.h"
#include "fcfs_queue.h"

#define MAX_PROCESS_COUNT 100

int main(int argc, char *argv[])
{
    int count = 0, selectedNum, processCount = 0;
    int flag = 1;

    process processList[MAX_PROCESS_COUNT];

    if (argc > 1)
    {
        count = getProcessInputFile(argv[1], processList, &processCount);
    }
    else
    {
        count = getProcessInput(processList, &processCount);
    }

    if (count <= 0)
    {
        printf("데이터를 입력받는 중 오류가 발생하였습니다.");
    }
    else
    {
#ifdef DEBUG
        for (int i = 0; i < count; ++i)
        {
            printf("%d %d %d %d\n", processList[i].type, processList[i].process_id, processList[i].priority, processList[i].computing_time);
        }
#endif
        while (flag)
        {
            result *schedulingList = (result *)malloc(sizeof(result) * count);
            switch (selectedNum = showMenu())
            {
            case 1:
                // round-robin
                round_robin(processList, count, 20, schedulingList);
                show_round_robin(processList, schedulingList, processCount);
                // srtf
                // scheduling1(processList,args, schedulingList);
                // showOutput(schedulingList);
                break;
            case 2:
                priority_scheduling(processList, count, 20, schedulingList);
                show_priority(schedulingList, processCount);
                break;
            case 3:
                fcfs_scheduling(processList, count, schedulingList);
                break;
            case -1:
                flag = 0;
                break;
            }
            free(schedulingList);
        }
    }

    return 0;
}

int showMenu()
{
    int inputData;
    printf("-----------Menu-----------\n");
    printf(" 원하는 스케줄링 방식을 입력하시오. \n");
    printf(" 1 : [  ]  round_robin sheduling. \n");
    printf(" 2 : [  ]  priority sheduling. \n");
    printf(" 3 : [  ]  fcfs sheduling. \n");
    printf(" -1 : 종료 \n");
    scanf("%d", &inputData);

    return inputData;
}