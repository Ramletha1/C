#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a,b,c,d;

    printf("Insert your Width and Height ");
    printf("\nWidth: ");
    scanf("%f",&a);
    printf("Height: ");
    scanf("%f",&b);

    c=a*b;
    d=(a*b)/2;

    printf("\n\n%10s%10s%10s%10s","","Width","Height","Area");
    printf("\n\n%10s%10.3f%10.3f%10.3f","Rectangle",a,b,c);
    printf("\n\n%10s%10.3f%10.3f%10.3f","Triangle",a,b,d);
    printf("\n\n");

    return 0;
}
