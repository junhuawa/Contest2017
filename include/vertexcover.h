#ifndef __VERTEX_H__
#define __VERTEX_H__

int read_data(char * data);
int get_standalone_nodes_number(int num);
int get_one_link_nodes_number(int num);
void print_edges(int num);
void print_cell(int num);
int find_link_another_node_and_remove(int j, int num);

#endif
