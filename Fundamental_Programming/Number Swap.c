#include <stdio.h>
#include <stdlib.h>

int main()
{
    int input;

    printf("This is number reverser.\nEnter your number: ");
    scanf("%d",&input);

    while(input>0){
        printf("%d",input%10);
        input/=10;
    }

    return 0;
}
