#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "question3.h"

int snap_fingers(int N, long K)
{
    int least_snaps;
    least_snaps = (1<<N) -1;

    //printf("N: %d, K: %d, least: %d\n", N, K, least_snaps);

    if(K%(1<<N) == least_snaps) {
        return ON;
    }
    return OFF;
}

#ifndef __UT__
int main(void)
#else
int main_func3(void)
#endif
{
    int case_num = 0;
    int N, K;
    int i;
    int result;

    scanf("%d\n", &case_num);
    for(i = 0; i < case_num; i++) {
        scanf("%d %d\n", &N, &K);
        result = snap_fingers(N, K);
       printf("Case #%d: %s\n", i+1, result==OFF? "OFF": "ON"); 
    }

    
    return 0;
}
