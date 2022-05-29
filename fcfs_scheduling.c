#include "process.h"
#include "result.h"
#include "fcfs_scheduling.h"
#include "fcfs_queue.h"

#include <stdlib.h>
#include <string.h >
#include <stdio.h>
//#include "priority_queue.h"
//#include "priority_scheduling.h"
#define MAX_QUEUE_SIZE 10





void fcfs_scheduling(process* processList, unsigned int size, Result* resultList) {	//�ڷ����� unsigned�� ������ 0�̻��� ���� ǥ����.

	process* newProcessList = (process*)malloc(sizeof(process) * size);	// ó�� �Է��ߴ� ���� ������� �ʱ� ���ؼ� ���ο� �Է� ����Ʈ ����
	memcpy(newProcessList, processList, sizeof(process) * size);	//ó�� �ԷµǾ��� ���μ��� ����(processList)���� newProcessList�� ���� �Ѵ�.
	int start_time[30] = { 0 };	//ť���� �۾��� �����ϴ� ���۽ð��� ���ϱ� ���� �迭
	int arrive_time[30] = { 0 };	//ť�� ������ �ð��� ���ϱ� ���� �迭
	int scheduling_time = 0;	//�����ٸ��� ����� ������ 1�� ������ //�����ð��� ���ϱ� ���� ����
	int queue_start_time = 0;	//queue�� ���۽ð��� ���ϱ� ���� ����
	QueueType queue;
	int element;
	int count = 0;
	Result saveprocessList[100] = { 0 };	//�۾��� ��ģ ���μ��� ������ ���� ���� �迭

	init_queue(&queue);	//����ť �ʱ�ȭ

	for (int i = 0; i < size; i++) {

		/*type�� 0 �Էµ� ���*/
		if (newProcessList[i].type == 0) {	//type�� 0 �̶�� 1) ready queue�� ����! 2) queue�� ���� �����ð��� ������
			
			//count++;
			saveprocessList[count].process_id = newProcessList[i].process_id;
			saveprocessList[count].priority = newProcessList[i].priority;
			saveprocessList[count].computing_time = newProcessList[i].computing_time;
			
			element = saveprocessList[count].process_id;	//pid�� element�� ��������
			enqueue(&queue, element);	//����ť�� ��������

		

			/*�����ð� ���ϱ�*/
			if (scheduling_time == 0) {	//type�� 0�̸� �ʱ� �����ð��� 0 
				arrive_time[count] = 0;
			}	
			else {
				arrive_time[count] = start_time[scheduling_time];	//�����ٸ��� ����Ǿ� scheduling_time�� 0�� �ƴ϶�� ���� ���μ����� ���۽ð��� �����ð� ��.
			}


			/*���۽ð� ���ϱ�*/
			if (element == 1) { start_time[count] = 0; }	//���� ù ��° ���μ����̸� ���� ť ���� ���� �ð��� 0�̵ȴ�.
			else if (element == 2) { start_time[count] = saveprocessList[count - 1].computing_time; }
			else {
				start_time[count] = start_time[count - 1] + saveprocessList[count - 1].computing_time;	//�ش� ���μ��� ���� ���μ��� computing_time�� ���۽ð��� �ȴ�.
			}
			count++;
			continue;
		}	

		/*type�� 1 �Էµ� ���*/
		if (newProcessList[i].type == 1) {	//type�� 1 �̶�� 1) ready queue �����ϱ� 2)�۾��� �������Ƿ� resultList�� ����		
			element = dequeue(&queue);	//���� ť�� �� �տ� �ִ� ģ�� ���� �� ���μ��� ���� ���� �޴´�.

			saveprocessList[element - 1].turnaround_time = start_time[element - 1] + saveprocessList[element - 1].computing_time - arrive_time[element - 1];
			scheduling_time +=1;	//�����ٸ��� ����Ǹ� 1�����Ѵ�.
			
			continue;
			
		 }
		
		//queue_start_time += 1;	//���۽ð� 1�����Ѵ�.

		/*type�� -1 �Էµ� ���*/
		if (newProcessList[i].type == -1) {	//�Է¿Ϸ� �Ǿ��ٴ� ���̹Ƿ� ������� ����ť���� �۾� ����
			break;
			
		}

	}

	while (!is_empty(&queue)) {	//ť�� �� ������ ��� �����ٸ�
		element = dequeue(&queue);	//���� ť�� �� �տ� �ִ� ģ�� ���� �� ���μ��� ���� ���� �޴´�.

		saveprocessList[element - 1].turnaround_time = start_time[element - 1] + saveprocessList[element - 1].computing_time - arrive_time[element - 1];
	}

	int sum_turnaround_time = 0;
	printf("--------------����� ���1-------------------------------\n");
	printf("Process_id, priority, computing_time, turn_around_time\n");
	
	for (int i = 0; i < count; i++) {
		printf("%d\t     %d\t\t    %d\t\t    %d\n", saveprocessList[i].process_id, saveprocessList[i].priority, saveprocessList[i].computing_time, saveprocessList[i].turnaround_time);
		sum_turnaround_time += saveprocessList[i].turnaround_time;
	}	
	printf("\naverage turn_around_time : %d \n", sum_turnaround_time / count);

}

