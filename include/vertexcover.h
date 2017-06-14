#ifndef __VERTEX_H__
#define __VERTEX_H__

#define MAX_NODE 10240
#define INDEBUG 0

extern int edges[MAX_NODE];
extern int state[MAX_NODE];
int read_data(char * data);
int get_standalone_nodes_number(int num);
int get_one_link_nodes_number(int num);
void print_edges(int num);
void print_cell(int num);
bool find_link_another_node_and_remove(int j, int num);
int get_optimal_nodes_number(int num);
int get_covered_linked_nodes_number(int num);
int get_covered_linked_nodes_number_by_brute_force(int num);
int revmove_links_already_covered(int num);

int break_the_graph(int num);
#endif
