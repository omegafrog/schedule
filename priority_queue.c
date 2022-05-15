#include<stdio.h>
#include<stdlib.h>

#include "priority_queue.h"

void push(priority_queue** head, process* new) {    //Ư�� ť�� ���� ���μ��� �����͸� ����

	if ((*head)->processData == NULL) { (*head)->processData = new; } //���� ť�� ó���� ���Դٸ� �ٷ� ����.

	else {
		priority_queue* newSpace = malloc(sizeof(priority_queue));  //ť�� ��Ÿ���� ���� ť ������ �Ҵ�޾� �ش� ���μ��� �����͸� ����
		newSpace->processData = new; //�ʱ�ȭ
		newSpace->next = NULL;

		priority_queue* cur = *head;
		priority_queue* pre = NULL;


		while (1) {
			if (cur == NULL) { pre->next = newSpace; break; } //���� ť�� ��ġ�� �ƹ��� ���ٸ� �ڱ� �ڽ��� �ִ´�.


			if (cur->processData->priority > newSpace->processData->priority) { //���� ť�� ������ �켱������ �۴ٸ� �ڱⰡ ���� ���� ť�� �ڷ� �δ�.
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



process* pop(priority_queue** head) { //���� �տ� �ִ� ���μ��� ������ ����.

	if ((*head)->processData == NULL) return NULL;

	process* selectedProcess;
	if ((*head)->next == NULL) { //���� �ڱⰡ ť�� �������̶�� head ���� NULL�� �Ѵ�.
		selectedProcess = (*head)->processData;
		(*head)->processData = NULL;

	}
	else {   //�ڱⰡ ť�� �������� �ƴ϶��, ���� ���� head�� �����ϰ� ���� ���� ������.
		priority_queue* temp = (*head);
		selectedProcess = (*head)->processData;
		(*head) = (*head)->next;

		free(temp); //�Ҵ�Ǿ��� �޸𸮸� �����Ѵ�.
	}
	return selectedProcess;

}


process* selectProcessFromQue(priority_queue** q1, priority_queue** q2, priority_queue** q3, priority_queue** q4) { //�� ť�� ��ȸ�ϸ� q1���� ���ʴ�� �ϳ��� ���� ������.

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

void insertProcessQue(priority_queue** q1, priority_queue** q2, priority_queue** q3, priority_queue** q4, process* processData) { //���μ����� �켱������ �´� ť�� ��ġ�� push�Ѵ�.

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