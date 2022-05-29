#include "process.h"
#include "result.h"
#include "fcfs_scheduling.h"
#include "fcfs_queue.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_QUEUE_SIZE 10

void fcfs_scheduling(process *processList, unsigned int size, result *resultList)
{ //자료형에 unsigned가 붙으면 0이상의 값만 표현함.

	process *newProcessList = (process *)malloc(sizeof(process) * size); // 처음 입력했던 값이 변경되지 않기 위해서 새로운 입력 리스트 생성
	memcpy(newProcessList, processList, sizeof(process) * size);		 //처음 입력되었던 프로세스 정보(processList)들을 newProcessList에 복사 한다.
	int start_time[30] = {0};											 //큐에서 작업을 시작하는 시작시간을 구하기 위한 배열
	int arrive_time[30] = {0};											 //큐에 도착한 시간을 구하기 위한 배열
	int scheduling_time = 0;											 //스케줄링이 실행될 때마다 1씩 증가됨 //도착시간을 구하기 위한 변수
	QueueType queue;
	int element;
	int count = 0;					   // type이 0일 때 들어오는 프로세스들의 갯수를 구하기 위한 변수
	result saveprocessList[100] = {0}; //작업을 마친 프로세스 정보들 저장 위한 배열

	init_queue(&queue); //레디큐 초기화

	for (int i = 0; i < size; i++)
	{

		/*type이 0 입력될 경우*/
		if (newProcessList[i].type == 0)
		{ // type이 0 이라면 1) ready queue에 들어가자! 2) queue에 들어온 도착시간을 구하자

			saveprocessList[count].process_id = newProcessList[i].process_id; // newProcessList의 프로세스 정보들을 saveprocessList 배열에 옮긴다.
			saveprocessList[count].priority = newProcessList[i].priority;	  //이 작업을 수행하는 이유는 type이 1 입력되었을 경우 process_id, priority, computing_time이 없기 때문에 저장하지 않기 위함이다.
			saveprocessList[count].computing_time = newProcessList[i].computing_time;

			element = saveprocessList[count].process_id; // 프로세스를 element에 대입하자
			enqueue(&queue, element);					 //레디큐에 삽입하자

			/*도착시간 구하기*/
			if (scheduling_time == 0)
			{ // type이 0이면 초기 도착시간은 0
				arrive_time[count] = 0;
			}
			else
			{
				arrive_time[count] = start_time[scheduling_time]; //스케줄링이 실행되어 scheduling_time이 0이 아니라면 다음 프로세스의 시작시간이 도착시간 됨.
			}

			/*시작시간 구하기*/
			if (element == 1)
			{
				start_time[count] = 0;
			} //만약 첫 번째 프로세스이면 레디 큐 내의 시작 시간은 0이된다.
			else if (element == 2)
			{
				start_time[count] = saveprocessList[count - 1].computing_time;
			}
			else
			{
				start_time[count] = start_time[count - 1] + saveprocessList[count - 1].computing_time; //해당 프로세스 전의 프로세스 computing_time이 시작시간이 된다.
			}
			count++;
			continue;
		}

		/*type이 1 입력될 경우*/
		if (newProcessList[i].type == 1)
		{							   // type이 1 이라면 1) ready queue 삭제하기 2) 작업을 마쳤으므로 resultList에 저장
			element = dequeue(&queue); //레디 큐에 맨 앞에 있는 프로세스 삭제 후 프로세스 값을 리턴 받는다.

			/*반환시간 구하기*/
			saveprocessList[element - 1].turnaround_time = start_time[element - 1] + saveprocessList[element - 1].computing_time - arrive_time[element - 1];
			scheduling_time += 1; //스케줄링이 실행되면 1증가한다.

			continue;
		}

		/*type이 -1 입력될 경우*/
		if (newProcessList[i].type == -1)
		{ //입력완료 되었다는 뜻이므로 순서대로 레디큐에서 작업 실행
			break;
		}
	}

	while (!is_empty(&queue))
	{							   //큐가 빌 때까지 계속 스케줄링
		element = dequeue(&queue); //레디 큐에 맨 앞에 있는 프로세스 삭제 후 프로세스 값을 리턴 받는다.

		/*반환시간 구하기*/
		saveprocessList[element - 1].turnaround_time = start_time[element - 1] + saveprocessList[element - 1].computing_time - arrive_time[element - 1];
	}

	int sum_turnaround_time = 0;
	printf("------------------- Scheduling Output --------------------------\n");
	printf("Process_id\t priority\t computing_time\t turn_around_time\n");

	for (int i = 0; i < count; i++)
	{
		printf("%d\t\t %d\t\t %d\t\t %d\n", saveprocessList[i].process_id, saveprocessList[i].priority, saveprocessList[i].computing_time, saveprocessList[i].turnaround_time);
		sum_turnaround_time += saveprocessList[i].turnaround_time;
	}
	printf("\naverage turn_around_time : %d \n", sum_turnaround_time / count);
}
