#include <stdio.h>
#include <stdlib.h>

int x = 100;
char y = 'A';
int z;

int func(int);

int main(void){
  x = func(5);
  printf("%d\n",x);
  return 0;
}

int func(int a)
{
int *b, *c;

b = malloc(sizeof(int));
c = malloc(sizeof(int));
*b = 3; *c = 2;

printf("<Heap Segment>\n");
printf("Address of *b = %p\n", b);
printf("Data of *b = %d\n", *b);
printf("Address of *c = %p\n", c);
printf("Data of *c = %d\n", *c);
  a += x+3;

printf("<Stack Segment>\n");
printf("Address of c = %p\n", &c);
printf("Data of c = %p\n", c);
printf("Address of b = %p\n", &b);
printf("Data of b = %p\n", b);
printf("Address of a = %p\n", &a);
printf("Data of a = %d\n", a);
printf("Address of RBP = %p\n", &a + 2);
printf("Data of RBP = 0x%x%08x\n", *(&a + 2), *(&a + 1));
printf("Address of rAdd = %p\n", &a + 4);
printf("Data of rAdd = 0x%x%08x\n", *(&a + 4), *(&a + 3));

while (1);

return a;
}