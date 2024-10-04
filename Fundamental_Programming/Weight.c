#include <stdio.h>
#include <stdlib.h>

int main()
{
    int s1,l1,o1,s2,l2,o2,sum,avg,st,lb,oz;

    printf("Input your first object's weight: ");
    scanf("%d,%d,%d",&s1,&l1,&o1);
    printf("\nInput your second object's weight: ");
    scanf("%d,%d,%d",&s2,&l2,&o2);




    printf("\n\n%-15s%-10s%-10s%-10s","","St.","Lb.","Oz.");
    printf("\n==========================================");
    printf("\n%-15s%-10d%-10d%-10d","  Weight1",s1,l1,o1);
    printf("\n%-15s%-10d%-10d%-10d","  Weight2",s2,l2,o2);
    printf("\n==========================================");
    printf("\n%-15s%-10d%-10d%-10d","Sum",s1+s2+(l1+l2+((o1+o2)/16))/14,l1+l2+((o1+o2)/16)%14,(o1+o2)%16);
    printf("\n%-15s%-10.2f%-10.2f%-10.2f","Average",(float)(s1+s2+(l1+l2+((o1+o2)/16))/14)/2,(float)((l1+l2+((o1+o2)/16))%14)/2,(float)((o1+o2)%16)/2);

    return 0;
}
