#include <stdio.h>
#include <stdlib.h>
#include <string.h >
#include "result.h"
#include "process.h"
#include "priority_queue.h"
#include "priority_scheduling.h"



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

	priority_queue* q1 = malloc(sizeof(priority_queue));  //q1~ q4���� ��ũ�� ����Ʈ ���� �� �ʱ�ȭ
	q1->processData = NULL;
	q1->next = NULL;
	priority_queue* q2 = malloc(sizeof(priority_queue));
	q2->processData = NULL;
	q2->next = NULL;
	priority_queue* q3 = malloc(sizeof(priority_queue));
	q3->processData = NULL;
	q3->next = NULL;
	priority_queue* q4 = malloc(sizeof(priority_queue));
	q4->processData = NULL;
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
				curTime += selectedProcess->remain_computing_time;
				selectedProcess->end_time = curTime;   //���μ����� ������ �������Ƿ� end�ð��� ����ϰ� �ش� ������ resultList�� ����
				completeTask(&resultList[++completeCount], selectedProcess);

			}
			else if (selectedProcess->remain_computing_time > quantTime) { //�ǽð� ���μ����� �ƴϸ�, �ð��Ҵ緮���� ū computing �ð��� ������ �ִٸ�
				curTime += quantTime;
				selectedProcess->remain_computing_time -= quantTime;  //�ð��Ҵ緮 ��ŭ ���
				(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);
				insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); //10��ŭ �켱������ ���� �ٽ� ť�� �ֱ�. (31�̻��̶�� 31 ����)

			}
			else { //���� �ð��Ҵ緮���� ���� �۴ٸ�
				curTime += selectedProcess->remain_computing_time;
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
			curTime += selectedProcess->remain_computing_time;
			selectedProcess->end_time = curTime;
			completeTask(&resultList[++completeCount], selectedProcess);

		}
		else if (selectedProcess->remain_computing_time > quantTime) {
			curTime += quantTime;
			selectedProcess->remain_computing_time -= quantTime;  //�ð��Ҵ緮 ��ŭ ���
			(selectedProcess->priority > 21) ? (selectedProcess->priority = 31) : (selectedProcess->priority += 10);

			insertProcessQue(&q1, &q2, &q3, &q4, selectedProcess); //10��ŭ �켱������ ���� �ٽ� ť�� �ֱ�. (31�̻��̶�� 31 ����)

		}
		else { //���� �ð��Ҵ緮���� ���� �۴ٸ�
			curTime += selectedProcess->remain_computing_time;
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

void completeTask(Result* resultList, process* completeProcess) { //�� ���� ��ģ ���μ����� turnaround�� ������ ������ ���� ������� ����Ѵ�.

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