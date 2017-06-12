#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int g_follow_level[1024];

typedef struct
{
    int extra;
    int sum;
}thumbsup_t;

thumbsup_t get_needed_extra_friends(int Fmax, int follow_level[])
{
    thumbsup_t thumbs;
    int extra = 0;

    memset(&thumbs, 0, sizeof(thumbsup_t));

    if(Fmax == 0) {
        thumbs.extra = (follow_level[0] == 0)? 1 : 0;
        thumbs.sum = follow_level[0] + thumbs.extra;
        //printf("Fmax: %d, extra: %d, sum: %d\n", Fmax, thumbs.extra, thumbs.sum);
        return thumbs;
    }

    thumbs = get_needed_extra_friends(Fmax - 1, follow_level);
    if(thumbs.sum < Fmax) {
        extra = Fmax - thumbs.sum;
        thumbs.extra += extra;
        thumbs.sum += extra + follow_level[Fmax];
        //printf("Fmax: %d, extra: %d, sum: %d\n", Fmax, thumbs.extra, thumbs.sum);
        return thumbs;
    }

    thumbs.sum += follow_level[Fmax];
    return thumbs;
}

int get_extra_friends_number(int Fmax, int follow_level[])
{
    thumbsup_t thumbs;

    thumbs = get_needed_extra_friends(Fmax, follow_level);
    return thumbs.extra;
}

void print_follow_levels(int Fmax)
{
    int i = 0;

    printf("Levels: ");
    for(i = 0; i < Fmax + 1; i++)
    {
        printf("%2d", g_follow_level[i]);
    }
    printf("\n");

}

int read_follow_levels(int Fmax, char * buf)
{
    int i = 0;
    while( i < Fmax + 1) {
        g_follow_level[i] = buf[i] - '0';
        i ++;
    }
    return  i;
}

#ifndef __UT__
int main(void)
#else
int main_func2(void)
#endif
{
    int case_num = 0;
    int Fmax = 0;
    int i;
    char buf[1024];

    scanf("%d\n", &case_num);
    if(case_num <= 0) return -1;
    //printf("case num: %d\n", case_num);
    
    for(i = 0; i < case_num; i++) {

        if(fgets(buf, sizeof(buf), stdin) != NULL) {
            //printf("Read buf: %s\n", buf);
            Fmax = atoi(buf);
            //printf("Fmax: %d\n", Fmax);
            if(Fmax < 0) {
                return -1;   
            }

            read_follow_levels(Fmax, strchr(buf, ' ')+1 );
            printf("Case #%d: %d\n", i+1, get_extra_friends_number(Fmax, g_follow_level));
        }

    }

    return 0;
}
