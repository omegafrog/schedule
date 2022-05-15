#ifndef __SCHEDULING_H__
#include "process.h"
#include "result.h"
#define __SCHEDULING_H__
// 스케줄링 구현 함수를 기록하는 자ㅜ
void round_robin(process *processList, unsigned int size, unsigned int quantTime, result *resultList);

#endif