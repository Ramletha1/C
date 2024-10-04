#include <stdio.h>
#include <stdlib.h>
#define R radius
#define A Area
#define P Pi

int main()
{
    float R,A,P;
    P=3.14;

    printf("Insert your Radius: ");
    scanf("%f",&R);
    A=R*P;
    printf("\n%.2f",A);


    return 0;
}
