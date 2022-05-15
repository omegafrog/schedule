#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "schedule.h"
#include "result.h"
#include "process.h"


#define MAX_PROCESS_COUNT 100



int getProcessInput(process*, int*);
int showMenu();


int main()
{

	int count, selectedNum, processCount;
	processCount = 0;
	int flag = 1;
	process processList[MAX_PROCESS_COUNT];

	count = getProcessInput(processList, &processCount);

	if (count < 0)
	{
		printf("�����͸� �Է¹޴� �� ������ �߻��Ͽ����ϴ�.");
	}
	else
	{
		while (flag)
		{
			Result* schedulingList = (Result*)malloc(sizeof(Result) * count);
			switch (selectedNum = showMenu())
			{
			case 1:
				break;
			case 2:
				priority_scheduling(processList, count, 20, schedulingList);
				printf("---------------------Schedulling Output ------------------------------\n");
				for (int i = 0; i < processCount; i++) {

					printf("Process_id\t Queue_id \t\t priority\t computing_time\t turn_around_time\n");
					printf("%d\t\t %-9s\t\t %d\t\t %d\t\t %d\n", schedulingList[i].process_id, schedulingList[i].process_qId, schedulingList[i].priority, schedulingList[i].computing_time, schedulingList[i].turnaround_time);

				}
				break;
			case 3:
				break;
			case 4:
				flag = 0;
				break;
			}
			
			free(schedulingList);
		}

	}

	for (int i = 0; i < count; ++i)
	{
		printf("%d %d %d %d\n", processList[i].type, processList[i].process_id, processList[i].priority, processList[i].remain_computing_time);
	}
	return 0;
}

// input �޴� �Լ�
int getProcessInput(process* processList, int* processCount)
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


		scanf("%d %d %d", &tmpProcess.process_id, &tmpProcess.priority, &tmpProcess.remain_computing_time);
		tmpProcess.computing_time = tmpProcess.remain_computing_time;
		processList[i] = tmpProcess;

	}
}

int showMenu()
{
	int inputData;
	printf("-----------Menu-----------\n");
	printf(" ���ϴ� �����ٸ� ����� �Է��Ͻÿ�. \n");
	printf(" 1 : [  ]  sheduling. \n");
	printf(" 2 : [  ]  sheduling. \n");
	printf(" 3 : [  ]  sheduling. \n");
	printf(" -1 : ���� \n");
	scanf("%d", &inputData);

	return inputData;
}



