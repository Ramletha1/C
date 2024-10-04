#include <stdio.h>
#include <stdlib.h>

int main()
{

    int h1,m1,s1,h2,m2,s2;

    printf("Enter your Starting Time (h:m:s): ");
    scanf("%d:%d:%d",&h1,&m1,&s1);
    printf("\nEnter your Ending Time (h:m:s): ");
    scanf("%d:%d:%d",&h2,&m2,&s2);

    printf("\nThe Total Time It takes is: %d:%d:%d",(h2+h1+(m1+m2+(s1+s2)/60)/60),(m1+m2+(s1+s2)/60)%60,(s1+s2)%60);

    return 0;
}
