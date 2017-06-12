#ifndef __QUESTION_4_H__
#define __QUESTION_4_H__

#define DISTRICT_NUM 1024+1
void init(void);
extern int weight[DISTRICT_NUM][DISTRICT_NUM];
extern int map[DISTRICT_NUM][DISTRICT_NUM];
int get_shortest_total_length(int num);
void display_weight(int num);

#endif

