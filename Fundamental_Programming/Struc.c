#include <stdio.h>
#define SIZE 5

struct student{
    char name[20];
    double score;
    char grade;
};

void main(){

    int i;
    int high=0;
    char highstudent;

    struct student st[SIZE];

    for(i=0;i<SIZE;i++){
        printf("Name[%d]: ",i+1);
        scanf("%s",st[i].name);
        printf("Score: ");
        scanf("%lf",&st[i].score);
        if(st[i].score>high){
            high=st[i].score;
            highstudent=i;
        }

        if(st[i].score>=90) st[i].grade='A';
        else if(st[i].score>=80) st[i].grade='B';
        else if(st[i].score>=70) st[i].grade='C';
        else if(st[i].score>=60) st[i].grade='D';
        else if(st[i].score<60) st[i].grade='F';
        }
    printf("\n\nList:\n");

    for(i=0;i<SIZE;i++){
        printf("\nStudent No.%d: %s",i+1,st[i].name);
        printf("\nScore: %.2lf",st[i].score);
        printf("\nGrade: %c",st[i].grade);
        puts("");
        }
    printf("\n%s got the highest grade at %d or %c",st[highstudent].name,high,st[highstudent].grade);
    printf("\n\n");
}
