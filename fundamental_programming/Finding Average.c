#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,d,e,x; //a=num count,b=counter,c=each num,d=sum,e=indicator,x=average(answer)
    printf("Input your number count: ");
    scanf("%d", &a); //Input Number Count (A).
    printf("\n");

    b=0;
    d=0;
    e=a;

    while(b<a) //Looping until B is not less than A, B=B+1 each loop.
{
    printf("%d Numbers required\n",e); //Indicator for Number Count Required
    printf("Input your number amount: ");
    scanf("%d", &c);
    e--; //Alternatively, e=e-1
    b++; //Alternatively, b=b+1
    d=d+c;
    printf("\nCurrent Sum is %d\n",d);
}
    {
        printf("\nTo find the average: Dividing overall sum by number count.\n");
        printf("Which mean %d divide by %d\n",d,a);
        x=d/a; //X for average answer, D for Total Sum, A for Number Count.
        printf("Answer is %d\n",x);

    }

    return 0;
}
