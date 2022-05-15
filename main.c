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


// ť�� ����ü ���·� ����
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
		printf("%d %d %d %d\n", processList[i].type, processList[i].process_id, processList[i].priority, processList[i].computing_time);
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
		
		
		scanf("%d %d %d", &tmpProcess.process_id, &tmpProcess.priority, &tmpProcess.computing_time);
		tmpProcess.init_computing_time = tmpProcess.computing_time;
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

void priority_scheduling(process* processList, unsigned int size,
	unsigned int quantTime, Result* resultList)
{
	// ���� �Է��� ������Ű�� �ʱ� ���ؼ� ���ο� �Է� ����Ʈ ����
	process* newProcessList = (process*)malloc(sizeof(process) * size);
	memcpy(newProcessList, processList, sizeof(process) * size);
	process* curProcess = NULL; //�Է¹��� ����Ʈ���� ������ �ϳ��� ���μ���
	process* selectedProcess = NULL;  // �����ٸ����� ���õǾ� ť���� pop�� ���μ���


	int curTime = 0; //���� cpu�� ���ð�
	int completeCount = -1; // ������ ��ģ ���μ��� ��

	que* q1 = malloc(sizeof(que));  //q1~ q4���� ��ũ�� ����Ʈ ���� �� �ʱ�ȭ
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



	for (int i = 0; i < size; i++) {   //�Է¹��� ���� ��ȸ�ϸ� ť�� �ְų� ���� ����
		curProcess = newProcessList + i;

		if (curProcess->type == 0) {   //���� 0��type�̶�� �켱������ �°� ������ ť�� push
			curProcess->start_time = curTime;  //���� ������ start�ð� ���

			insertProcessQue(&q1, &q2, &q3, &q4, curProcess);

		}

		else if (curProcess->type == 1) { //1�� type�� ���Դٸ�, �켱������ �°� �ϳ��� ���μ����� ���� ����


			selectedProcess = selectProcessFromQue(&q1, &q2, &q3, &q4);
			if (selectedProcess->priority < 1) { //���� ������ ���μ����� �ǽð� ���μ����̸� computing�ð��� ���� ���
				curTime += selectedProcess->computing_time;  
				selectedProcess->end_time = curTime;   //���μ����� ������ �������Ƿ� end�ð��� ����ϰ� �ش� ������ resultList�� ����
				completeTask(&resultList[++completeCount], selectedProcess);

			}
			else if (selectedProcess->computing_time > quantTime) { //�ǽð� ���μ����� �ƴϸ�, �ð��Ҵ緮���� ū computing �ð��� ������ �ִٸ�
				curTime += quantTime;
				selectedProcess->computing_time -= quantTime;  //�ð��Ҵ緮 ��ŭ ���
				(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);
				insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); //10��ŭ �켱������ ���� �ٽ� ť�� �ֱ�. (31�̻��̶�� 31 ����)

			}
			else { //���� �ð��Ҵ緮���� ���� �۴ٸ�
				curTime += selectedProcess->computing_time;  
				selectedProcess->end_time = curTime;    //���� �ð��� ���� ����ð��� ��� �� resultList�� ��� ����
				completeTask(&resultList[++completeCount], selectedProcess);

			}

		}
		else {
			printf("<ERROR> type���� 0�� 1�� �ƴմϴ�. ���α׷��� �����մϴ�. \n "); //0�� 1�� �ƴ� Ÿ���� ���� ������ ����
			exit(1);
		}

	}

	while (1) {  //ť���� ��� �����͸� ���� �� ���� �ݺ�

		selectedProcess = selectProcessFromQue(&q1, &q2, &q3, &q4); //�켱������ �ϳ��� ���μ����� ť���� ����

		if (selectedProcess == NULL) break; //��� ť���� ���� �����Ͱ� ���ٸ� break;

		if (selectedProcess->priority < 1) { //�ǽð� ���μ����̸� ��� �ð��� ��� �� resultList�� ���� ����
			curTime += selectedProcess->computing_time;
			selectedProcess->end_time = curTime;
			completeTask(&resultList[++completeCount], selectedProcess);

		}
		else if (selectedProcess->computing_time > quantTime) {
			curTime += quantTime;
			selectedProcess->computing_time -= quantTime;  //�ð��Ҵ緮 ��ŭ ���
			(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);

			insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); //10��ŭ �켱������ ���� �ٽ� ť�� �ֱ�. (31�̻��̶�� 31 ����)

		}
		else { //���� �ð��Ҵ緮���� ���� �۴ٸ�
			curTime += selectedProcess->computing_time;
			selectedProcess->end_time = curTime;
			completeTask(&resultList[++completeCount], selectedProcess); //���� �ð��� ���� ����ð��� ��� �� resultList�� ��� ����
			

		}

	}

	//�Ҵ��ߴ� �޸𸮸� �����Ѵ�.
	free(q1);
	free(q2);
	free(q3);
	free(q4);
	free(newProcessList);

}

void push(que** head, process* new) {    //Ư�� ť�� ���� ���μ��� �����͸� ����

	if ((*head)->prpcessData == NULL) { (*head)->prpcessData = new; } //���� ť�� ó���� ���Դٸ� �ٷ� ����.

	else {
		que* newSpace = malloc(sizeof(que));  //ť�� ��Ÿ���� ���� ť ������ �Ҵ�޾� �ش� ���μ��� �����͸� ����
		newSpace->prpcessData = new; //�ʱ�ȭ
		newSpace->next = NULL;

		que* cur = *head;
		que* pre = NULL;


		while (1) {
			if (cur == NULL) { pre->next = newSpace; break; } //���� ť�� ��ġ�� �ƹ��� ���ٸ� �ڱ� �ڽ��� �ִ´�.


			if (cur->prpcessData->priority > newSpace->prpcessData->priority) { //���� ť�� ������ �켱������ �۴ٸ� �ڱⰡ ���� ���� ť�� �ڷ� �δ�.
				if (cur == (*head)) {  //���� ������ ť�� ��ġ�� �� ���̶�� �տ� ��ġ��Ų��.
					newSpace->next = cur;
					(*head) = newSpace;
					break;
				}
				else if (cur == NULL) { //���� ������ ��ġ�� ť�� �������̶�� �ڱ� �ڽ��� �������� ��ġ��Ų��.
					pre->next = newSpace;
					cur = newSpace;
					break;
				}
				else { //�׷��� �ʴٸ� ���� ��ġ�� ��ġ��Ų��.
					pre->next = newSpace;
					newSpace->next = cur;
					break;
				}
			}
			else {  // ���� ������ ��ġ�� �ƴ϶�� �ڽ��� �ڷΰ���.
				pre = cur;
				cur = cur->next;
			}
		}
	}
}



process* pop(que** head) { //���� �տ� �ִ� ���μ��� ������ ����.

	if ((*head)->prpcessData == NULL) return NULL;

	process* selectedProcess;
	if ((*head)->next == NULL) { //���� �ڱⰡ ť�� �������̶�� head ���� NULL�� �Ѵ�.
		selectedProcess = (*head)->prpcessData;
		(*head)->prpcessData = NULL;

	}
	else {   //�ڱⰡ ť�� �������� �ƴ϶��, ���� ���� head�� �����ϰ� ���� ���� ������.
		que* temp = (*head);
		selectedProcess = (*head)->prpcessData;
		(*head) = (*head)->next;

		free(temp); //�Ҵ�Ǿ��� �޸𸮸� �����Ѵ�.
	}
	return selectedProcess;

}

process* selectProcessFromQue(que** q1, que** q2, que** q3, que** q4) { //�� ť�� ��ȸ�ϸ� q1���� ���ʴ�� �ϳ��� ���� ������.

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

void insertProcessQue(que** q1, que** q2, que** q3, que** q4, process* processData) { //���μ����� �켱������ �´� ť�� ��ġ�� push�Ѵ�.

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

void completeTask(Result* resultList, process* completeProcess) { //�� ���� ��ģ ���μ����� turnaround�� ������ ������ ���� ������� ����Ѵ�.

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