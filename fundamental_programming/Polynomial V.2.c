#include <stdio.h>
#include <math.h>
int main()
{
    int a,b,c;
    double sq, ans1, ans2;

    // ax^2+bx+c

    printf("Input your 3 Coefficients: ");
    scanf("%d %d %d",&a,&b,&c);
    printf("\n");

    sq=(b*b)-(4*a*c); // For If sq<0.

 // Display as ax^2+bx+c.
    if(a!=0){ // x^2
    switch(a){
        case 1: printf("x^2"); break;
        case -1: printf("-x^2"); break;
        default: printf("%dx^2",a); break;
        }
    }

    if(a!=0 && b>0){ // print b
        printf("+");}
    if(b!=0){
    switch(b){
        case 1: printf("x"); break;
        case -1: printf("-x"); break;
        case 0: break;
        default: printf("%dx",b);
        }
    }

    if(c!=0){ // print c
        if(a!=0 | b!=0){
            if(c<0)
            printf("%d",c);
            if(c>0)
            printf("+%d",c);
        }
    }


    if(a==0 && b==0){ // no value output.
        switch(c){
        case 0: printf("------"); break;
        default: printf("%d",c); break;
        }
        printf("C2");
    }

    printf("\n");

// BELOW IS ANSWER & CALCULATION OUTPUT //

if(sq<0){ // If sq<0 Forced Return.
        printf("\nNo Solutions");
        printf("\n\n\nOutput no.1");
        return 0; // Input 1 0 1
}

if(a!=0 && b!=0 && c!=0){ // a,b,c isn't zero.
    ans1=(-b+sqrt(pow(b,2)-(4*a*c)))/(2*a);
    ans2=(-b-sqrt(pow(b,2)-(4*a*c)))/(2*a);
    printf("\nThere are 2 possible answer.");
    printf("\nPositive = %.3lf",ans1);
    printf("\nNegative = %.3lf",ans2);
    printf("\n\n\nOutput no.2");
    return 0; // Input 1 2 1
}

if(a==0 && sq>=0){ // IF a=0, change formula.
    ans1=-c/b;
    switch(b){
    case 0:printf("\nNo Solutions"); break;
    default:printf("\nAnswer = %.2lf",ans1); break;
    }
    printf("\n\n\nOutput no.3");
    return 0; // Input 0 1 1
}

/*if(b==0 && sq>=0){
    ans1=(-b+sqrt(pow(b,2)-(4*a*c)))/(2*a);
    ans2=(-b-sqrt(pow(b,2)-(4*a*c)))/(2*a);
    printf("Positive = %.3lf",ans1);
    printf("Negative = %.3lf",ans2);
    printf("\n\n\nOutput no.4");
    return 0;
}
*/

// Comment above* is unconverted formula.

if(b==0 && sq>=0){ // IF b=0, change formular
    ans1=(sqrt(-(4*a*c)))/(2*a);
    ans2=(-sqrt(-(4*a*c)))/(2*a);
    printf("\nThere are 2 possible answer.");
    printf("\nPositive = %.3lf",ans1);
    printf("\nNegative = %.3lf",ans2);
    printf("\n\n\nOutput no.5");
    return 0; // Input -1 0 1
}
}
