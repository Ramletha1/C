#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,min,max;
    printf("Input 3 numbers (a:b:c) : ");
    scanf("%d:%d:%d",&a,&b,&c);

    if(a<=b && a<=c) min=a;
    else if(b<=c) min=b;
    else min=c;

    if(a>=b && a>=c) max=a;
    else if(b>=c) max=b;
    else max=c;

    printf("\n");
    printf("\n%d is the minimum.",min);
    printf("\n%d is the maximum",max);

    return 0;
}
