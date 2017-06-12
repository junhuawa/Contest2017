#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NODE_NUM (2000 + 1)
#define LINKED 1

int cell[NODE_NUM][NODE_NUM];

int read_links(char *buf, int num)
{
    int a, b;
    char * p = buf;

    while(p != NULL) {
        a = atoi(p);
        p = strchr(p, ' ') + 1;
        b = atoi(p);
        printf("%d, %d\n", a, b);
        cell[a][b] = cell[b][a] = LINKED;

        p = strchr(p, ' ');
        if(!p) break;
        p = p+1;
    }
    return 0;
}

void print_cell(num)
{
    int i, j;
    printf("cell: %d\n", num);
    for(i=1; i<=num; i++) {
        for(j=1; j<=num; j++) {
            printf("%d ", cell[i][j]);
        }
        printf("\n");
    }
}

int read_data(void)
{
    int num;
    char buf[1024];

    memset(buf, 0, sizeof(buf));
    memset(cell, 0, sizeof(cell));

    fgets(buf, sizeof(buf), stdin);
    num = atoi(buf);
    read_links(strchr(buf, ' ') + 1, num);
    print_cell(num);
    return 0;
}


#ifndef __UT__
int main(void)
#else
int main_func5(void)
#endif
{
    int i;
    int case_num;
    scanf("%d\n", &case_num);
    printf("case: %d\n", case_num);

    for(i=0; i<case_num; i++) {
        read_data();
    }
    
    return 0;
}
