#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_NODE 101
#define INDEBUG 0

int8_t graph[MAX_NODE][MAX_NODE];//int -> int8_t
int edges[MAX_NODE], nodes[MAX_NODE], state[MAX_NODE];

int t,m,n,k,a,b;

bool nodigit(char *p);
int read_links(char *buf, int num)
{
    int a, b;
    char * p = buf;
    int count = 0;
    p = strchr(buf, ' ');
    if(!p){
        return 0;
    }
    p = p+1;

    while(p != NULL) {
        a = atoi(p);
        p = strchr(p, ' ') + 1;
        b = atoi(p);
        //printf("%d, %d\n", a, b);
        graph[a][b] = graph[b][a] = 1;
        edges[a]++;
        edges[b]++;
        count ++;

        p = strchr(p, ' ');
        if(!p) break;
        p = p+1;
        if(nodigit(p)) { 
            break;
        }
    }
    return count;
}

bool nodigit(char *p)
{
    int i;
    for(i=0; i<strlen(p); i++) {
        if(isdigit(p[i])!= 0) {
            return false;
        }
    }
    return true;
}

void init_graph(int num){

    for (int i=0; i<= num; i++) {
        for (int j=0; j<= num; j++) {
            graph[i][j]=0;
        }
    }
}

void init_env(int num){

    memset(edges, 0, sizeof(edges));
    memset(state, 0, sizeof(state));
    memset(nodes, 0, sizeof(nodes));

    for (int i=0; i <= num; i++) {
        edges[i]=0;
        state[i]=0;
        nodes[i]=i;
    }
}

void print_cell(int num)
{
    int i, j;
    printf("cell: %d\n", num);
    for(i=1; i<=num; i++) {
        for(j=1; j<=num; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

/*
int parse_data(int num, int links){
    int k = 2;
    bool flag = false;

    return 0;
}
*/

#ifndef __UT__
int read_data(void)
{
    int num;
    int links_num = 0;
    char buf[1024];

    memset(buf, 0, sizeof(buf));

    fgets(buf, sizeof(buf), stdin);

    num = atoi(buf);
    init_graph(num);
    init_env(num);

    links_num = read_links(buf, num);
    print_cell(num);

    return num;
}
#else
int read_data(char * data)
{
    int num;
    int links_num = 0;
    char *buf = data;

    num = atoi(buf);
    init_graph(num);
    init_env(num);

    links_num = read_links(buf, num);
    print_cell(num);

    return num;
}
#endif


int get_standalone_nodes_number(int num){
    int count = 0;

    for(int i=1; i<=num; i++){
        if(edges[i] == 0){ 
            count ++;
        }
    }
    return count;
}

int get_one_link_nodes_number(int num){
    return 0;
}

#ifndef __UT__
int main() {
    int i;
    int case_num;
    int num = 0;

    scanf("%d\n", &case_num);

    for(i=0; i<case_num; i++) {
        num = read_data();
        printf("Case #%d: %d\n", i+1, num);
    }

    return 0;
}
#endif
