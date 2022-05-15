#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "result.h"
#include "process.h"
#include "queue.h"

void round_robin(process *processList, unsigned int size,
                 unsigned int quantTime, result *resultList)
{
    // 본래 입력을 오염시키지 않기 위해서 새로운 입력 리스트 생성
    process *newProcessList = (process *)malloc(sizeof(process) * size);
    memcpy(newProcessList, processList, sizeof(process) * size);

    // make new ready queue
    ReadyQueue *readyQueue = (ReadyQueue *)malloc(sizeof(readyQueue));
    initQueue(readyQueue);

    // clock time
    int clock = 0;

    // 입력으로 들어온 프로세스 리스트를 순회하면서 type1이 나올때까지 readyQueue적재
    // type1이 나오면 스케쥴링 시작 신호. RR이므로 가장 먼저 들어온 프로세스를 pop한다
    process *curProcess = NULL;
    process *runningProcess = NULL;
    for (int i = 0; i < size; ++i)
    {
        curProcess = newProcessList + i;

        if (curProcess != NULL)
        {
            switch (curProcess->type)
            {
            case 0:
                curProcess->startClockTime=clock;
                push(readyQueue, curProcess);
                break;
            case 1:
                runningProcess = pop(readyQueue);
                // // 시작된 적이 없는 프로세스라면 시작 시간을 기록
                // if (runningProcess->startClockTime == -1)
                // {
                //     runningProcess->startClockTime = clock;
                // }
                // 프로세스 수행
                // 프로세스의 computing time이 quantum time보다 긴 경우
                // quantum time만큼 시간이 흐르고
                // computing time에서 quantum time만큼 빼준다
                // 그리고 이 프로세스는 다시 readyqueue에 들어간다.
                if (runningProcess->computing_time > quantTime)
                {
                    clock += quantTime;
                    runningProcess->computing_time -= quantTime;
                    push(readyQueue, runningProcess);
                }
                // 프로세스의 computing time이 quantum time보다 짧은 경우
                // computing time만큼 시간이 흐르고
                // endClockTime을 기록한다.
                // 이 프로세스는 종료되었으므로 다시 readyQueue에 들어가지 않는다.
                else
                {
                    clock += runningProcess->computing_time;
                    runningProcess->endClockTime = clock;
                }
                break;
            default:
                break;
            }
        }
    }
    // readyqueue에 남아있는 프로세스들이 없어질 때까지
    // 위의 행동을 반복
    while (!isEmpty(readyQueue))
    {
        process *runningProcess = pop(readyQueue);
        // if (runningProcess->startClockTime == -1)
        // {
        //     runningProcess->startClockTime = clock;
        // }

        if (runningProcess->computing_time > quantTime)
        {
            clock += quantTime;
            runningProcess->computing_time -= quantTime;
            push(readyQueue, runningProcess);
        }
        else
        {
            clock += runningProcess->computing_time;
            runningProcess->endClockTime = clock;
        }
    }

    // 결과를 resultList에 저장
    // turnaroundTime = endClockTime - startClockTime
    // 이외는 동일 결과.
    for (int i = 0; i < size; ++i)
    {
        curProcess = newProcessList + i;
        resultList[i].process_id = curProcess->process_id;
        resultList[i].priority = curProcess->priority;
        resultList[i].computing_time = curProcess->computing_time;
        resultList[i].turnaround_time = curProcess->endClockTime - curProcess->startClockTime;
    }
    // 동적할당한 메모리 해제
    free(newProcessList);
    free(readyQueue);
}