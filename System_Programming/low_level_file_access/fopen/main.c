#include <stdio.h>

int main(void){
  int c;
  FILE *in, *out;

  in = fopen("file.in","rt");
  out = fopen("file.out","wt");

  while((c = getc(in)) != EOF)
    putc(c,out);

  fclose(in);
  fclose(out);
  return 0;
}