#include <stdio.h>
#include <stdlib.h>

void main(){

    int input,space,print,i;

    printf("Input your number: ");
    scanf("%d",&input);
    puts("");

    for(i=0;i<input;i++){
        for(space=input-i;space>0;space--){
            printf(" ");
        }
        for(print=i;print>0;print--){
            printf("**");
        }
        puts("");
    }

    for(i=input;i>0;i--){
        for(space=input-i;space>0;space--){
            printf(" ");
        }
        for(print=i;print>0;print--){
            printf("**");
        }
        puts("");
    }

    printf("\n\n\n");
    diamond2();
}


void diamond2(){

    int input,space,print,i;

    printf("Enter your number: ");
    scanf("%d",&input);

    for(i=0;i<=input;i++){
        for(space=input-i;space>0;space--){
            printf("%4c",' ');
        }
        for(print=i;print>0;print--){
                printf("%4d",i);
        }
        for(print=i;print>0;print--){
            printf("%5.1lf",(float)input/i);
        }
        puts("");
    }

    for(i=input-1;i>0;i--){
        for(space=input-i;space>0;space--){
            printf("%4c",' ');
        }
        for(print=i;print>0;print--){
            printf("%4d",i);
        }
        for(print=i;print>0;print--){
            printf("%5.1lf",(float)input/i);
        }
        puts("");
    }
}


