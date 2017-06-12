#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <queue>
using namespace std;
#include "question4.h"

#define MAX_DISTANCE 100000


int dist[DISTRICT_NUM];

int weight[DISTRICT_NUM][DISTRICT_NUM];

int known[DISTRICT_NUM];
int parent[DISTRICT_NUM];

struct cmp{
    bool operator()(int v1, int v2){
        //printf("cmp: %d, %d\n", dist[v1], dist[v2]);
        return dist[v1] > dist[v2];
    }
};

int insert_data(int row[], char *buf)
{
    int i = 1;
    char  *p = buf;
    row[i]= atoi(buf);

    i++;
    while((p = strchr(p, ' '))) {
        p = p+1;

        while(*p == ' ') {
            p = p+1;
        }

        row[i] = atoi(p);
        i++;
    }
    return i;
}

void show_parent(int num){

    int i;

    printf("parent: \n");
    for(i = 1; i<num+1; i++) {
        printf("(%2d, %2d) ", i, parent[i]);
    }
    printf("\n");
    return;
}

void show_distance(int num){

    int i;

    printf("Distance: \n");
    for(i = 1; i<num+1; i++) {
        printf("%5d ", dist[i]);
    }
    printf("\n");
    return;
}

int sum_dist(int num)
{
    int i;
    int sum = 0;
    for(i = 2; i<num+1; i++) {
        sum += weight[i][parent[i]];
    }
    return sum;
}

void display_weight(int num)
{
    int i, j;
    for(i = 1; i<num+1; i++) {
        for(j = 1; j<num+1; j++) {
            printf("%4d ", weight[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void insert_link(int num)
{
    int i;
    int a, b;

    for(i=1; i<=num; i++) {
        scanf("%d %d\n", &a, &b);
        weight[a][b] = 0;
        weight[b][a] = 0;
    }
}

void display_known_table(int num){

    for(int i=1; i<= num; i++){
        printf("%d ", known[i] == false? 0:1);
    }
    printf("\n");
}

void init_known_table(int num){

    for(int i=1; i<= num; i++){
            known[i] = false;
    }
}

void init_dist_table(int num){

    for(int i=1; i<= num; i++){
            dist[i] = MAX_DISTANCE;
    }
}

void init(void){
    memset(dist, 0, sizeof(dist));
    memset(known, 0, sizeof(known));
    memset(weight, 0, sizeof(weight));
    memset(parent, 0, sizeof(parent));

}

int get_shortest_total_length(int num)
{
    int V;

    init_dist_table(num);
    init_known_table(num);

    priority_queue<int , vector<int>, cmp > q;

    dist[1] = 0;
    parent[1] = 1;
    q.push(1);

    while(!q.empty()){
        V = q.top();
        //printf("top(%d)\n", V);

        known[V] = true;

        for(int i = 1; i<num+1; i++){
            assert((known[i] == false) || (known[i] == true));
            if(!known[i]){
               // if(dist[V] + weight[V][i] < dist[i]){
                //    dist[i] = dist[V] + weight[V][i];
                if(weight[V][i] < dist[i]){
                    dist[i] = weight[V][i];

                    //printf("push id: %d, dist: %d, parent: %d\n", i, dist[i], V);
                    q.push(i);
                    parent[i] = V;
                }
            }
        }
        
        q.pop();
    }
    //show_distance(num);
    //show_parent(num);
    return sum_dist(num);
}

void read_weight(int num){
    char buf[1024];

    for(int i=1; i<num+1; i++) {
        if(fgets(buf, sizeof(buf), stdin) != NULL) {
            insert_data(weight[i], buf);
            //printf("weight num: %d\n", insert_data(weight[i], buf));
        }
    }
}

#ifndef __UT__
int main(void)
#else
int main_func4(void)
#endif
{

    int num;

    int case_num;
    int link_num;

    scanf("Case #%d:\n", &case_num);
    scanf("%d\n", &num);

    init();
    read_weight(num);

    scanf("%d\n", &link_num);
    insert_link(link_num);
    
    printf("Case#%d: %d\n", case_num, get_shortest_total_length(num));

    return 0;
}
