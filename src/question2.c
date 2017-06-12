#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "question2.h"
long nodeid[4096];
int tree[4096];
subtask_t tasklist[4096];
int idcounter = 0;

int getIdPosition(long src)
{
    int i;
    for(i = 0; i < 4096; i++) {
        if(nodeid[i] == src)
            return i;
    }
    return -1;
}

int get_one_sub_task_result(subtask_t *p, long task_id)
{
    int i;

    for (i=0; i<SUB_TASK_NUM; i++) {
        if(p->subtask[i] == 0) {
            return -1;
        }

        if(p->subtask[i] == task_id) {
            return p->results[i];
        }
    }
    return -1;
}

void insert_sub_task_id(subtask_t *p, long subtask[])
{
    int i, tmp;
    int results[SUB_TASK_NUM];
    memset(results, FAIL, sizeof(results));
    
    for(i=0; i<SUB_TASK_NUM; i++) {
        if(subtask[i] == 0) {
           break;
        }
        tmp = get_one_sub_task_result(p, subtask[i]);

        //printf("subtask: %d, res: %d\n", subtask[i], tmp);

        if(tmp != -1) {
            results[i] = tmp;
        }
    }
    memcpy(p->subtask, subtask, SUB_TASK_NUM * sizeof(long));
    memcpy(p->results, results, SUB_TASK_NUM * sizeof(int));
    return;
}

int insert_task(long src, long target, long subtask[])
{
    int srcpos, targetpos;

    srcpos = getIdPosition(src);
    if(srcpos == -1) {
        if(idcounter == 0) {
            nodeid[0] = src;
            tree[0] = -1;
        }
        srcpos = idcounter;
        idcounter ++;
    }

    targetpos = getIdPosition(target);
    if(targetpos == -1) {
        targetpos = idcounter;
        idcounter ++;
    }

    nodeid[targetpos] = target;
    tree[targetpos] = srcpos;
    insert_sub_task_id(&tasklist[targetpos], subtask);

    return idcounter;
}

int set_subtask_result(subtask_t *p, long task_id, int result)
{
    int i;
    for(i=0; i<SUB_TASK_NUM; i++) {
        if(p->subtask[i] == task_id) {
            p->results[i] = result;
            return 0;
        }

        if(p->subtask[i] == 0) {
            p->subtask[i] = task_id;
            p->results[i] = result;
            return 0;
        }
    }
    return -1;
}

void append_sub_task_id(subtask_t *p, long task_id)
{
    int i;
    for(i=0; i<SUB_TASK_NUM; i++) {
        if(p->subtask[i] == 0) {
            p->subtask[i] = task_id;
            return;
        }
    }
    return;
}

int tell_result(long target, long sub_task_id, int result)
{
    int targetpos;
    targetpos = getIdPosition(target);
    if(targetpos == -1) {
        targetpos = idcounter;
        idcounter ++;
        nodeid[targetpos] = target;
    }
    set_subtask_result(&tasklist[targetpos], sub_task_id, result);

    return 0;
}

bool is_subtask_success(subtask_t *p)
{
    int i;

    for(i=0; p->subtask[i] != 0; i++) {
        if(p->results[i] == FAIL) {
            return false;
        }
    }
    return true;
}

int get_subtask_failed_number(subtask_t *p)
{
    int i;
    int count = 0;

    for(i=0; p->subtask[i] != 0; i++) {
        if(p->results[i] == FAIL) {
            count ++;
        }
    }
    return count;
}

int get_node_depth(int idx)
{
    int count = 0;

    while(tree[idx] != -1) {
        idx = tree[idx];
        count ++;
    }

    return count;
}

void print_report(void)
{
    int count;
    int i;
    int fail_results[4096];

    memset(fail_results, 0, sizeof(fail_results));

    for(i=1; i<idcounter; i++) {
        if(!is_subtask_success(&tasklist[i])) {
            fail_results[tree[i]] ++;
        }
    }

    for(i=0; i<idcounter; i++) {
        if(fail_results[i]!= 0) { 
            printf("{%d, %ld, %d}\n", get_node_depth(i), nodeid[i], fail_results[i]);
        }
    }
}

void init_task(void)
{
    int i;
    memset(nodeid, 0, sizeof(nodeid));
    memset(tree, 0, sizeof(tree));
    memset(tasklist, 0, sizeof(tasklist));
    for(i=0; i<4096; i++) {
        memset(tasklist[i].results, FAIL, sizeof(int) * NODE_ID_NUM);
    }
    idcounter = 0;
}

int parse_sub_task_list(char *p, long subtask[])
{
    char *end;
    int i=0;
    //printf("sub task list: %s\n", p);

    p = p+1;
    end = strchr(p, '}');
    while(p < end) {
       subtask[i] = atol(p);
       //printf("task: %ld\n", subtask[i]);
       p = strstr(p, ", ");
       i++;
       if(!p) break;
       p = p+2;
    }
    return i;
}

void parse_insert_cmd(char *buf)
{
    long src, target;
    char *p;
    long subtask[SUB_TASK_NUM];

    memset(subtask, 0, sizeof(subtask));

    sscanf(buf, "{%ld, %ld, List", &src, &target);

    p = strchr(buf, '(');
    parse_sub_task_list(p, subtask);

    insert_task(src, target, subtask);
}

void parse_tell_result(char *buf)
{
    long target, sub_task_id;

    sscanf(buf, "{%ld, %ld, ", &target, &sub_task_id);
    if(strstr(buf, "Success")) {
        tell_result(target, sub_task_id, SUCCESS);
    }else {
        tell_result(target, sub_task_id, FAIL);
    }
}

#ifndef __UT__
int main(void)
#else
int main_func(void)
#endif
{
    char buf[1024];
    init_task();

    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        if(strstr(buf, "List")) {
            parse_insert_cmd(buf);
        }else {
            parse_tell_result(buf);
        }
    }

    print_report();
    return 0;
}
