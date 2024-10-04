#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 3

int main()
{
    char inp[SIZE][30],first[30],last[30];
    int i1,i2;

    for(i1=0;i1<SIZE;i1++){
        gets(inp[i1]);
    }

    strcpy(first,inp[0]);
    if(strcmp(first,inp[1])>0 )
        strcpy(first,inp[1]);
    if(strcmp(first,inp[2])>0 )
        strcpy(first,inp[2]);

    strcpy(last,inp[0]);
    if(strcmp(last,inp[1])<0 )
        strcpy(last,inp[1]);
    if(strcmp(last,inp[2])<0 )
        strcpy(last,inp[2]);


    printf("\nFirst = %s ",first);
    printf("\nLast = %s ",last);

    char comb[30];
    strcat(comb,first);
    strcat(comb,last);
    i2=comb;

    for(i1=0;i1<strlen(comb);i1++){
        comb[i1]=tolower(comb[i1]);
        if(comb[i1]=='a' || comb[i1]=='e' || comb[i1]=='i' || comb[i1]=='o' || inp[i1]=='u'){
            comb[i1]=toupper(comb[i1]);
        }
    }
    printf("\n%s",comb);
}
