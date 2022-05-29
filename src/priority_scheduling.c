#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "result.h"
#include "process.h"
#include "priority_queue.h"
#include "priority_scheduling.h"

void priority_scheduling(process *processList, unsigned int size,
						 unsigned int quantTime, result *resultList)
{
	// 본래 입력을 오염시키지 않기 위해서 새로운 입력 리스트 생성
	process *newProcessList = (process *)malloc(sizeof(process) * size);
	memcpy(newProcessList, processList, sizeof(process) * size);

	process *curProcess = NULL;		 //입력받은 리스트에서 꺼내올 하나의 프로세스
	process *selectedProcess = NULL; // 스케줄링으로 선택되어 큐에서 pop된 프로세스

	int curTime = 0;		//현재 cpu의 사용시간
	int completeCount = -1; // 수행을 마친 프로세스 수

	priority_queue *q1 = malloc(sizeof(priority_queue)); // q1~ q4까지 링크드 리스트 선언 및 초기화
	q1->processData = NULL;
	q1->next = NULL;
	priority_queue *q2 = malloc(sizeof(priority_queue));
	q2->processData = NULL;
	q2->next = NULL;
	priority_queue *q3 = malloc(sizeof(priority_queue));
	q3->processData = NULL;
	q3->next = NULL;
	priority_queue *q4 = malloc(sizeof(priority_queue));
	q4->processData = NULL;
	q4->next = NULL;

	for (int i = 0; i < size; i++)
	{ //입력받은 값을 순회하며 큐에 넣거나 값을 꺼냄
		curProcess = newProcessList + i;

		if (curProcess->type == 0)
		{									  //만약 0번type이라면 우선순위에 맞게 적합한 큐로 push
			curProcess->start_time = curTime; //들어온 시점의 start시간 기록
			insertProcessQue(&q1, &q2, &q3, &q4, curProcess);
		}

		else if (curProcess->type == 1)
		{ // 1번 type이 들어왔다면, 우선순위에 맞게 하나의 프로세스를 꺼내 실행

			selectedProcess = selectProcessFromQue(&q1, &q2, &q3, &q4);
			if (selectedProcess == NULL)
			{
				printf("<ERROR> 현재 큐에 어떠한 프로세스도 대기중이지 않습니다. 유효하지 않은 요청입니다. \n");
				exit(1);
			}
			if (selectedProcess->priority < 1)
			{ //만약 꺼내온 프로세스가 실시간 프로세스이면 computing시간을 전부 사용
				curTime += selectedProcess->remain_computing_time;
				selectedProcess->end_time = curTime; //프로세스의 수행을 마쳤으므로 end시간을 기록하고 해당 정보를 resultList에 저장
				completeTask(&resultList[++completeCount], selectedProcess);
			}
			else if (selectedProcess->remain_computing_time > quantTime)
			{ //실시간 프로세스가 아니며, 시간할당량보다 큰 computing 시간을 가지고 있다면
				curTime += quantTime;
				selectedProcess->remain_computing_time -= quantTime; //시간할당량 만큼 사용
				(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);
				insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); // 10만큼 우선순위를 더해 다시 큐에 넣기. (31이상이라면 31 고정)
			}
			else
			{ //만약 시간할당량보다 값이 작다면
				curTime += selectedProcess->remain_computing_time;
				selectedProcess->end_time = curTime; //남은 시간에 대한 종료시간을 기록 후 resultList에 결과 저장
				completeTask(&resultList[++completeCount], selectedProcess);
			}
		}
		else
		{
			printf("<ERROR> type값이 0과 1이 아닙니다. 프로그램을 종료합니다. \n "); // 0과 1이 아닌 타입의 값이 들어오면 종료
			exit(1);
		}
	}

	while (1)
	{ //큐에서 모든 데이터를 꺼낼 때 까지 반복

		selectedProcess = selectProcessFromQue(&q1, &q2, &q3, &q4); //우선순위가 하나의 프로세스를 큐에서 꺼냄

		if (selectedProcess == NULL)
			break; //모든 큐에서 꺼낼 데이터가 없다면 break;

		if (selectedProcess->priority < 1)
		{ //실시간 프로세스이면 모든 시간을 사용 후 resultList에 상태 저장
			curTime += selectedProcess->remain_computing_time;
			selectedProcess->end_time = curTime;
			completeTask(&resultList[++completeCount], selectedProcess);
		}
		else if (selectedProcess->remain_computing_time > quantTime)
		{
			curTime += quantTime;
			selectedProcess->remain_computing_time -= quantTime; //시간할당량 만큼 사용
			(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);

			insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); // 10만큼 우선순위를 더해 다시 큐에 넣기. (31이상이라면 31 고정)
		}
		else
		{ //만약 시간할당량보다 값이 작다면
			curTime += selectedProcess->remain_computing_time;
			selectedProcess->end_time = curTime;
			completeTask(&resultList[++completeCount], selectedProcess); //남은 시간에 대한 종료시간을 기록 후 resultList에 결과 저장
		}
	}

	//할당했던 메모리를 해제한다.
	free(q1);
	free(q2);
	free(q3);
	free(q4);
	free(newProcessList);
}

void completeTask(result *resultList, process *completeProcess)
{ //할 일을 마친 프로세스는 turnaround를 포함한 정보를 끝난 순서대로 기록한다.

	resultList->priority = completeProcess->priority;
	resultList->computing_time = completeProcess->computing_time;
	resultList->process_id = completeProcess->process_id;
	resultList->turnaround_time = completeProcess->end_time - completeProcess->start_time;

	if (resultList->priority < 0)
		strcpy(resultList->process_qId, "real_time");

	else if (((resultList->priority - 1) / 10 + 1) == 1)
		strcpy(resultList->process_qId, "Q1");

	else if (((resultList->priority - 1) / 10 + 1) == 2)
		strcpy(resultList->process_qId, "Q2");

	else if (((resultList->priority - 1) / 10 + 1) == 3)
		strcpy(resultList->process_qId, "Q3");
	else if (((resultList->priority - 1) / 10 + 1) == 4)
		strcpy(resultList->process_qId, "Q4");
}