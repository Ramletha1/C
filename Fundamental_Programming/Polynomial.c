#include <stdio.h>
#include <math.h>
int main()
{
    double a,b,c,x1,x2;

    printf("Input your polynomial as ax^2+bx+c\n\n");
    scanf("%lfx^2+%lfx+%lf",&a,&b,&c);

    x1=(-b+sqrt(pow(b,2)-(4*a*c)))/(2*a);
    x2=(-b-sqrt(pow(b,2)-(4*a*c)))/(2*a);

    printf("\n\nx1 = %lf",x1);
    printf("\nx2 = %lf",x2);

    return 0;
}
