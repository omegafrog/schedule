#include<stdio.h>
#include<stdlib.h>

#include "priority_queue.h"

void push(priority_queue** head, process* new) {    //특정 큐에 대해 프로세스 데이터를 삽입

	if ((*head)->processData == NULL) { (*head)->processData = new; } //만약 큐의 처음에 들어왔다면 바로 들어간다.

	else {
		priority_queue* newSpace = malloc(sizeof(priority_queue));  //큐로 나타내기 위해 큐 공간을 할당받아 해당 프로세스 데이터를 넣음
		newSpace->processData = new; //초기화
		newSpace->next = NULL;

		priority_queue* cur = *head;
		priority_queue* pre = NULL;


		while (1) {
			if (cur == NULL) { pre->next = newSpace; break; } //현재 큐의 위치에 아무도 없다면 자기 자신을 넣는다.


			if (cur->processData->priority > newSpace->processData->priority) { //현재 큐의 값보다 우선순위가 작다면 자기가 들어가고 지금 큐는 뒤로 민다.
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



process* pop(priority_queue** head) { //가장 앞에 있는 프로세스 정보를 뺀다.

	if ((*head)->processData == NULL) return NULL;

	process* selectedProcess;
	if ((*head)->next == NULL) { //만약 자기가 큐의 마지막이라면 head 값을 NULL로 한다.
		selectedProcess = (*head)->processData;
		(*head)->processData = NULL;

	}
	else {   //자기가 큐의 마지막이 아니라면, 다음 값을 head로 지정하고 현재 값은 날린다.
		priority_queue* temp = (*head);
		selectedProcess = (*head)->processData;
		(*head) = (*head)->next;

		free(temp); //할당되었던 메모리를 해제한다.
	}
	return selectedProcess;

}


process* selectProcessFromQue(priority_queue** q1, priority_queue** q2, priority_queue** q3, priority_queue** q4) { //각 큐를 순회하며 q1부터 차례대로 하나의 값을 꺼낸다.

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

void insertProcessQue(priority_queue** q1, priority_queue** q2, priority_queue** q3, priority_queue** q4, process* processData) { //프로세스의 우선순위에 맞는 큐의 위치에 push한다.

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