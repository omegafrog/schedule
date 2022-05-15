#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESS_COUNT 100



typedef struct _process
{
	int type;
	int process_id;
	int priority;
	int init_computing_time;
	int computing_time;
	int start_time;
	int end_time;
} process;

typedef struct _result
{
	int process_id;
	char process_qId[10];
	int priority;
	int computing_time;
	int turnaround_time;

} Result;


// 큐를 구조체 형태로 정의
typedef struct que_ {
	process* prpcessData;
	struct que_* next;
} que;

int getProcessInput(process*, int* );
int showMenu();
process* pop(que** head);
void push(que** head, process* new);
void priority_scheduling(process* processList, unsigned int size, unsigned int quantTime, Result* resultList);
process* selectProcessFromQue(que* q1, que* q2, que* q3, que* q4);
void insertProcessQue(que** q1, que** q2, que** q3, que** q4, process* processData);
void completeTask(Result* resultList, process* completeProcess);

int main()
{

	int count, selectedNum, processCount;
	processCount = 0;
	int flag = 1;
	process processList[MAX_PROCESS_COUNT];

	count = getProcessInput(processList, &processCount);

	if (count < 0)
	{
		printf("데이터를 입력받는 중 오류가 발생하였습니다.");
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
		printf("%d %d %d %d\n", processList[i].type, processList[i].process_id, processList[i].priority, processList[i].computing_time);
	}
	return 0;
}

// input 받는 함수
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
		
		
		scanf("%d %d %d", &tmpProcess.process_id, &tmpProcess.priority, &tmpProcess.computing_time);
		tmpProcess.init_computing_time = tmpProcess.computing_time;
		processList[i] = tmpProcess;
	
	}
}

int showMenu()
{
	int inputData;
	printf("-----------Menu-----------\n");
	printf(" 원하는 스케줄링 방식을 입력하시오. \n");
	printf(" 1 : [  ]  sheduling. \n");
	printf(" 2 : [  ]  sheduling. \n");
	printf(" 3 : [  ]  sheduling. \n");
	printf(" -1 : 종료 \n");
	scanf("%d", &inputData);

	return inputData;
}

void priority_scheduling(process* processList, unsigned int size,
	unsigned int quantTime, Result* resultList)
{
	// 본래 입력을 오염시키지 않기 위해서 새로운 입력 리스트 생성
	process* newProcessList = (process*)malloc(sizeof(process) * size);
	memcpy(newProcessList, processList, sizeof(process) * size);
	process* curProcess = NULL; //입력받은 리스트에서 꺼내올 하나의 프로세스
	process* selectedProcess = NULL;  // 스케줄링으로 선택되어 큐에서 pop된 프로세스


	int curTime = 0; //현재 cpu의 사용시간
	int completeCount = -1; // 수행을 마친 프로세스 수

	que* q1 = malloc(sizeof(que));  //q1~ q4까지 링크드 리스트 선언 및 초기화
	q1->prpcessData = NULL;
	q1->next = NULL;
	que* q2 = malloc(sizeof(que));
	q2->prpcessData = NULL;
	q2->next = NULL;
	que* q3 = malloc(sizeof(que));
	q3->prpcessData = NULL;
	q3->next = NULL;
	que* q4 = malloc(sizeof(que));
	q4->prpcessData = NULL;
	q4->next = NULL;



	for (int i = 0; i < size; i++) {   //입력받은 값을 순회하며 큐에 넣거나 값을 꺼냄
		curProcess = newProcessList + i;

		if (curProcess->type == 0) {   //만약 0번type이라면 우선순위에 맞게 적합한 큐로 push
			curProcess->start_time = curTime;  //들어온 시점의 start시간 기록

			insertProcessQue(&q1, &q2, &q3, &q4, curProcess);

		}

		else if (curProcess->type == 1) { //1번 type이 들어왔다면, 우선순위에 맞게 하나의 프로세스를 꺼내 실행


			selectedProcess = selectProcessFromQue(&q1, &q2, &q3, &q4);
			if (selectedProcess->priority < 1) { //만약 꺼내온 프로세스가 실시간 프로세스이면 computing시간을 전부 사용
				curTime += selectedProcess->computing_time;  
				selectedProcess->end_time = curTime;   //프로세스의 수행을 마쳤으므로 end시간을 기록하고 해당 정보를 resultList에 저장
				completeTask(&resultList[++completeCount], selectedProcess);

			}
			else if (selectedProcess->computing_time > quantTime) { //실시간 프로세스가 아니며, 시간할당량보다 큰 computing 시간을 가지고 있다면
				curTime += quantTime;
				selectedProcess->computing_time -= quantTime;  //시간할당량 만큼 사용
				(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);
				insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); //10만큼 우선순위를 더해 다시 큐에 넣기. (31이상이라면 31 고정)

			}
			else { //만약 시간할당량보다 값이 작다면
				curTime += selectedProcess->computing_time;  
				selectedProcess->end_time = curTime;    //남은 시간에 대한 종료시간을 기록 후 resultList에 결과 저장
				completeTask(&resultList[++completeCount], selectedProcess);

			}

		}
		else {
			printf("<ERROR> type값이 0과 1이 아닙니다. 프로그램을 종료합니다. \n "); //0과 1이 아닌 타입의 값이 들어오면 종료
			exit(1);
		}

	}

	while (1) {  //큐에서 모든 데이터를 꺼낼 때 까지 반복

		selectedProcess = selectProcessFromQue(&q1, &q2, &q3, &q4); //우선순위가 하나의 프로세스를 큐에서 꺼냄

		if (selectedProcess == NULL) break; //모든 큐에서 꺼낼 데이터가 없다면 break;

		if (selectedProcess->priority < 1) { //실시간 프로세스이면 모든 시간을 사용 후 resultList에 상태 저장
			curTime += selectedProcess->computing_time;
			selectedProcess->end_time = curTime;
			completeTask(&resultList[++completeCount], selectedProcess);

		}
		else if (selectedProcess->computing_time > quantTime) {
			curTime += quantTime;
			selectedProcess->computing_time -= quantTime;  //시간할당량 만큼 사용
			(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);

			insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); //10만큼 우선순위를 더해 다시 큐에 넣기. (31이상이라면 31 고정)

		}
		else { //만약 시간할당량보다 값이 작다면
			curTime += selectedProcess->computing_time;
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

void push(que** head, process* new) {    //특정 큐에 대해 프로세스 데이터를 삽입

	if ((*head)->prpcessData == NULL) { (*head)->prpcessData = new; } //만약 큐의 처음에 들어왔다면 바로 들어간다.

	else {
		que* newSpace = malloc(sizeof(que));  //큐로 나타내기 위해 큐 공간을 할당받아 해당 프로세스 데이터를 넣음
		newSpace->prpcessData = new; //초기화
		newSpace->next = NULL;

		que* cur = *head;
		que* pre = NULL;


		while (1) {
			if (cur == NULL) { pre->next = newSpace; break; } //현재 큐의 위치에 아무도 없다면 자기 자신을 넣는다.


			if (cur->prpcessData->priority > newSpace->prpcessData->priority) { //현재 큐의 값보다 우선순위가 작다면 자기가 들어가고 지금 큐는 뒤로 민다.
				if (cur == (*head)) {  //만약 들어가려는 큐의 위치가 맨 앞이라면 앞에 위치시킨다.
					newSpace->next = cur;
					(*head) = newSpace;
					break;
				}
				else if (cur == NULL) { //만약 들어가려는 위치가 큐의 마지막이라면 자기 자신을 마지막에 위치시킨다.
					pre->next = newSpace;
					cur = newSpace;
					break;
				}
				else { //그렇지 않다면 현재 위치에 위치시킨다.
					pre->next = newSpace;
					newSpace->next = cur;
					break;
				}
			}
			else {  // 만약 들어가려는 위치가 아니라면 자신은 뒤로간다.
				pre = cur;
				cur = cur->next;
			}
		}
	}
}



process* pop(que** head) { //가장 앞에 있는 프로세스 정보를 뺀다.

	if ((*head)->prpcessData == NULL) return NULL;

	process* selectedProcess;
	if ((*head)->next == NULL) { //만약 자기가 큐의 마지막이라면 head 값을 NULL로 한다.
		selectedProcess = (*head)->prpcessData;
		(*head)->prpcessData = NULL;

	}
	else {   //자기가 큐의 마지막이 아니라면, 다음 값을 head로 지정하고 현재 값은 날린다.
		que* temp = (*head);
		selectedProcess = (*head)->prpcessData;
		(*head) = (*head)->next;

		free(temp); //할당되었던 메모리를 해제한다.
	}
	return selectedProcess;

}

process* selectProcessFromQue(que** q1, que** q2, que** q3, que** q4) { //각 큐를 순회하며 q1부터 차례대로 하나의 값을 꺼낸다.

	process* selectedProcess = NULL;
	selectedProcess = pop(q1);


	if (selectedProcess == NULL) 
		selectedProcess = pop(q2);

	if (selectedProcess == NULL)
		selectedProcess = pop(q3);

	if (selectedProcess == NULL)
		selectedProcess = pop(q4);

	return selectedProcess;
}

void insertProcessQue(que** q1, que** q2, que** q3, que** q4, process* processData) { //프로세스의 우선순위에 맞는 큐의 위치에 push한다.

	process* curProcess = processData;

	switch ((curProcess->priority - 1) / 10)
	{
	case -1: //-10~ -9
		push(q1, curProcess);
		break;
	case 0: // -8~ 10
		push(q1, curProcess);
		break;
	case 1: // 11~20
		push(q2, curProcess);
		break;
	case 2: //21~30
		push(q3, curProcess);
		break;
	case 3: //31
		push(q4, curProcess);
		break;

	}

}

void completeTask(Result* resultList, process* completeProcess) { //할 일을 마친 프로세스는 turnaround를 포함한 정보를 끝난 순서대로 기록한다.

	resultList->priority = completeProcess->priority;
	resultList->computing_time = completeProcess->init_computing_time;
	resultList->process_id = completeProcess->process_id;
	resultList->turnaround_time = completeProcess->end_time - completeProcess->start_time;


	if (resultList->priority < 0)
		strcpy(resultList->process_qId, "real_time");

	else if(((resultList->priority - 1) / 10 + 1) == 1)
		strcpy(resultList->process_qId, "Q1");

	else if (((resultList->priority - 1) / 10 + 1) == 2)
		strcpy(resultList->process_qId, "Q2");

	else if (((resultList->priority - 1) / 10 + 1) == 3)
		strcpy(resultList->process_qId, "Q3");
	else if (((resultList->priority - 1) / 10 + 1) == 4)
		strcpy(resultList->process_qId, "Q4");





}