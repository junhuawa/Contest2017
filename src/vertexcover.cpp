#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include "vertexcover.h"
using namespace std;

enum statetype{
    UNCOVERED,
    COVERED
};

int8_t graph[MAX_NODE][MAX_NODE];//int -> int8_t
int edges[MAX_NODE], state[MAX_NODE];
int nodes_covered[MAX_NODE];

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
    //printf("count: %d\n", count);
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

bool is_covered(int i){
    return state[i] == COVERED;
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

    memset(nodes_covered, 0, sizeof(nodes_covered));

    for (int i=0; i <= num; i++) {
        edges[i]=0;
        state[i]=0;
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

void print_links(int num)
{
    int i;
    printf("links: %d\n", num);
    for(i=1; i<=num; i++) {
        for(int j=i+1; j<=num; j++){
            if(graph[i][j] == 1){
                printf("(%d %d)", i, j);
            }
        }
    }
    printf("\n");
}

void print_cell(int num)
{
    int i, j;
    printf("cell: %d\n", num);
    printf("    ");
    for(int i=1; i<=num; i++){
        printf("%d ", i%10); 
    }
    printf("\n");
    for(i=1; i<=num; i++) {
        printf("%2d: ", i);
        for(j=1; j<=num; j++) {
            if(graph[i][j] == 1) {
                printf("%d ", 1);
            } else if(graph[i][j] == 0){
                printf("  "); 
            }
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
    char buf[809200];

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

void cover_node(int i){
    state[i] = COVERED;
}

int get_standalone_nodes_number(int num){
    int count = 0;

//    printf("standalone: \n");
    for(int i=1; i<=num; i++){
        if(edges[i] == 0){ 
 //           printf("i: %d ", i);
            count ++;
            cover_node(i);
        }
    }
  //  printf("\n");
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
            cover_node(i);
            cover_node(j);
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

int remove_one_link(int i, int num)
{
    int j = 0;

    for(j=1; j<=num; j++){
        if(graph[i][j] == 1){
            //printf("link between %d and %d found\n", i, j);
            break;
        }
    }

    graph[i][j] = graph[j][i]= 0;
    edges[i] --;
    edges[j] --;
    //printf("remove link betwen %d and %d\n", i, j);
    return 0;
}

int remove_links_of(int j, int num, int backup[]){
    int count = 0;

    cover_node(j);
    //printf("remove : %d\n", j);
    for(int i=1; i<= num; i++){

        if(graph[i][j] == 1){
            remove_the_link_in_backup(i, j, backup);
            count ++;
            cover_node(i);
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

    i = find_node_with_max_links(num);
    remove_one_link(i, num);

    return 0;
}

int revmove_links_already_covered(int num){
    int count = 0;
    for(int i=1; i<=num; i++){
        for(int j=i; j<=num; j++){
            if(graph[i][j] == 1){
                if(is_covered(i) && is_covered(j)) {
                    graph[i][j] = graph[j][i] = 0;
                    edges[i] --;
                    edges[j] --;
                    count ++;
                }
            }
        }
    }
    return count;
}

int save_all_nodes(int nodes[], int num){
    int count = 0;
    for(int i=1; i<=num; i++){
        if(edges[i] > 0){
            nodes[count] = i; 
            count ++;
        }
    }
    return count;
}

bool all_nodes_covered(int nodes[], int nodes_num){

    for(int i=0; i<nodes_num; i++){
        if(nodes_covered[nodes[i]] == UNCOVERED){
            return false;
        }
    }
    return true;
}

void color_node(int index, int num){
    nodes_covered[index] = COVERED;

    for(int i=1; i<=num; i++){
        if(graph[index][i] == 1){
            nodes_covered[i] = COVERED;
        }
    }

    for(int i=1; i<=num; i++){
        if(graph[i][index] == 1){
            nodes_covered[i] = COVERED;
        }
    }
}

void color_the_nodes(int iter, int nodes[], int remain_nodes_num, int num){

    for(int i=0; i<remain_nodes_num; i++){
        if((iter & (1 << i)) == 1<<i){
            //printf("iter: %d, color nodes %d, realnode: %d\n", iter, i, nodes[i]);
           color_node(nodes[i], num); 
        }
    }
}

int get_covered_nodes_num(int iter, int nodes_num)
{
    int count = 0;

    for(int i=0; i<nodes_num; i++){
        if((iter & (1 << i)) == (1<<i)){
            count ++;
        }
    }
    return count;
}

void print_nodes_covered(int nodes[], int remain_nodes_num){

    for(int i=0; i<remain_nodes_num; i++){
        printf("node: %d, %c\n", nodes[i], nodes_covered[nodes[i]] == COVERED? 'C': ' ');
    }
}

int get_covered_linked_nodes_number_by_brute_force(int num){
    int remain_nodes[20];
    int remain_nodes_num = 0;
    int iter = 0;
    int least = 0;

    memset(remain_nodes, 0, sizeof(int));
    remain_nodes_num = save_all_nodes(remain_nodes, num);
    //printf("remain_nodes_num: %d\n", remain_nodes_num);
    
    least = remain_nodes_num;
    while(iter < (1<<remain_nodes_num) -1){
        //printf("iter: %d\n", iter);
        iter ++;
        memcpy(nodes_covered, state, sizeof(nodes_covered));
        color_the_nodes(iter, remain_nodes, remain_nodes_num, num);
        //print_nodes_covered(remain_nodes, remain_nodes_num);
        if(all_nodes_covered(remain_nodes, remain_nodes_num)){
            if(least > get_covered_nodes_num(iter, remain_nodes_num)){
                least = get_covered_nodes_num(iter, remain_nodes_num);
            }
        }
    }

    return least;
}

int get_covered_linked_nodes_number(int num)
{
    int covered_counter = 0;
    int sum = 0;
    int new_sum = 0;
    
    //print_cell(num);
    sum = links_sum(num);
    //printf("lins sum: %d\n", sum);
    while(sum != 0){
        covered_counter += get_one_link_nodes_number(num);
        //printf("covered_counter after one link: %d\n", covered_counter);
        covered_counter += get_optimal_nodes_number(num);
        revmove_links_already_covered(num);
        //printf("covered_nods_counter: %d\n", covered_counter);
        //print_cell(num);
        new_sum = links_sum(num);
        //printf("lins sum: %d\n", sum);
        if(new_sum == sum){
            //print_links(num);
            covered_counter += get_covered_linked_nodes_number_by_brute_force(num);
           //print_cell(num);
           //print_edges(num);
            //break_the_graph(num);
            //covered_counter += 1;
          //print_cell(num);
          //print_edges(num);
            //printf("graph loop encountered\n");
            break;
        }
        sum = new_sum;
    }
    
    //printf("count: %d\n", covered_counter);
    return covered_counter;
}


#ifndef __UT__
int get_results()
{
    int sum = 0;
    int num = 0;
    num = read_data();

    sum = get_standalone_nodes_number(num);
    //printf("standalone node: %d\n", sum);
    sum += get_covered_linked_nodes_number(num);

    return sum;
}

int main() {
    int i;
    int case_num;
    int sum = 0;

    scanf("%d\n", &case_num);

    for(i=0; i<case_num; i++) {
        //printf("Case: %d\n", i+1);
        sum = get_results();
        printf("Case #%d: %d\n", i+1, sum);
    }

    return 0;
}
#endif
