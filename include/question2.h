#ifndef __QUESTION_2_H__
#define __QUESTION_2_H__

#define SUB_TASK_NUM 20
#define NODE_ID_NUM 4096
typedef struct
{
    int results[SUB_TASK_NUM];
    long subtask[SUB_TASK_NUM];
}subtask_t;

enum result_type {
    FAIL,
    SUCCESS
};

extern long nodeid[NODE_ID_NUM];
extern int tree[NODE_ID_NUM];
extern subtask_t tasklist[NODE_ID_NUM];

void parse_insert_cmd(char *buf);
void parse_tell_result(char *buf);
int insert_task(long src, long target, long subtask[]);
int tell_result(long target, long sub_task_id, int result);
void print_report(void);
void init_task(void);
#endif

