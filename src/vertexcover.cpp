#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include "vertexcover.h"
using namespace std;


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
    for(i=0; i<(int)strlen(p); i++) {
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

void print_edges(int num)
{
    int i;
    printf("edges number: %d\n", num);
    for(i=1; i<=num; i++) {
        printf("%d ", edges[i]);
    }
    printf("\n");
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
    char buf[1024];

    memset(buf, 0, sizeof(buf));

    fgets(buf, sizeof(buf), stdin);

    num = atoi(buf);
    init_graph(num);
    init_env(num);

    read_links(buf, num);

    return num;
}
#else
int read_data(char * data)
{
    int num;
    char *buf = data;

    num = atoi(buf);
    init_graph(num);
    init_env(num);

    read_links(buf, num);

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

void remove_the_link_immediate(int i, int j){
    graph[i][j] = 0;
    graph[j][i] = 0; 
    edges[i] --;
    edges[j] --;
}

void remove_the_link_in_backup(int i, int j, int *backup){
    graph[i][j] = 0;
    graph[j][i] = 0; 
    backup[i] --;
    backup[j] --;
}

int find_link_another_node(int j, int num){
    for(int i=1; i<= num; i++){
        if(graph[j][i] == 1){
            return i;
        }
    }
    return 0;
}

bool find_link_another_node_and_remove(int j, int num){
    for(int i=1; i<= num; i++){
        if((graph[j][i] == 1) && (edges[i] == 1)){
            remove_the_link_immediate(i, j);
            return true;
        }
    }
    return false;
}

int get_one_link_nodes_number(int num){
    int count = 0;

    for(int i=1; i<=num; i++){
        if(edges[i] == 1){ 
            if(find_link_another_node_and_remove(i, num)){
                count ++;
            }
        }
    }
    return count;
}

int remove_links_of(int j, int num, int backup[]){
    int count = 0;

    for(int i=1; i<= num; i++){

        if(graph[i][j] == 1){
            remove_the_link_in_backup(i, j, backup);
            count ++;
        }
    }
    return count;
}

int get_optimal_nodes_number(int num){
    int j;
    int count = 0;
    //int links_count = 0;
    int backup[num + 1];
    memcpy(backup, edges, sizeof(backup));

    for(int i=1; i<=num; i++){
        //print_cell(num);
        //print_edges(num);
        if(edges[i] == 1){ 
            j = find_link_another_node(i, num);
            if( j == 0) continue;
            remove_links_of(j, num, backup);
            //links_count = remove_links_of(j, num, backup);
            //print_edges(num);
            //printf("i: %d Removed links of node: %d, links num: %d\n", i, j, links_count);
            count ++;
        }
        //printf("count: %d\n", count);
    }
    memcpy(edges, backup, sizeof(backup));
    return count;
}

int links_sum(int num){
    int sum = 0;

    for(int i=1; i<=num; i++){
        sum += edges[i];
    }

    return sum;
}

int find_node_with_max_links(int num){
    int links = 0;
    int pos = 0;

    for(int i=1; i<=num; i++){
        if((edges[i] != 0) && (edges[i] > links)){
            links = edges[i];
            pos = i;
        }
    }
    return pos;
}

int break_the_graph(int num)
{
    int i;
    int backup[num + 1];

    memcpy(backup, edges, sizeof(backup));

    i = find_node_with_max_links(num);
    remove_links_of(i, num, backup);

    memcpy(edges, backup, sizeof(backup));
    return 0;
}

int get_covered_linked_nodes_number(int num)
{
    int covered_counter;
    int sum = 0;
    int new_sum = 0;
    
    sum = links_sum(num);
    while(sum != 0){
        covered_counter += get_one_link_nodes_number(num);
        //printf("covered_counter after one link: %d\n", covered_counter);
        covered_counter += get_optimal_nodes_number(num);
        //printf("covered_nods_counter: %d\n", covered_counter);
        new_sum = links_sum(num);
        if(new_sum == sum){
//           print_cell(num);
//           print_edges(num);
            break_the_graph(num);
            covered_counter += 1;
 //          print_cell(num);
 //          print_edges(num);
            //printf("graph loop encountered\n");
            //break;
        }
        sum = new_sum;
    }
    
    return covered_counter;
}


#ifndef __UT__
int get_results()
{
    int sum = 0;
    int num = 0;
    num = read_data();

    sum = get_standalone_nodes_number(num);
    sum += get_covered_linked_nodes_number(num);

    return sum;
}

int main() {
    int i;
    int case_num;
    int sum = 0;

    scanf("%d\n", &case_num);

    for(i=0; i<case_num; i++) {
        sum = get_results();
        printf("Case #%d: %d\n", i+1, sum);
    }

    return 0;
}
#endif
