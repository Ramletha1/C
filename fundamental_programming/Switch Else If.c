#include <stdio.h>
#include <math.h>
int main()
{
    int a,b,c;
    float x1,x2;

    printf("Input your 3 Coefficients: ");
    scanf("%d %d %d",&a,&b,&c);

    x1=(-b+sqrt(pow(b,2)-(4*a*c)))/(2*a);
    x2=(-b-sqrt(pow(b,2)-(4*a*c)))/(2*a);

    switch(a){
        case 1: printf(" x^2"); break;
        case -1: printf(" -x^2"); break;
        case 0: break;
        default: printf(" %dx^2",a); break;
        }

    switch(b){
        case 1: printf(" x"); break;
        case -1: printf(" -x"); break;
        case 0: break;
        default: printf(" %dx",a);
        }
            if(b>0) printf("+");
            else if(b<0) printf("-");

    return 0;
}
