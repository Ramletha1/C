#include <stdio.h>
#include <stdlib.h>

void main()
{
    int inp,space,print,a,b,c,d,e;

    scanf("%d",&inp);

    for(a=0;a<=inp;a++){
        for(space=inp;space>a;space--){
            printf(" ");
        }
        for(print=0;print<a;print++){
            printf("**");
        }
        puts("");
    }

    for(a=inp;a>=0;a--){
        for(space=inp;space>a;space--){
            printf(" ");
        }
        for(print=a;print>0;print--){
            printf("**");
        }
        puts("");
    }
}
