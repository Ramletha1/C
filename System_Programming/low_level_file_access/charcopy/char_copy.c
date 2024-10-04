#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
char c;
int size;
int in;
int out;
in = open("file.in", O_RDONLY);
out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
while (read(in, &c, 1) == 1){
  write(out, &c, 1);
  size++;
}

  lseek(out,size/2,SEEK_SET);
  write(out,"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",16);
  lseek(in,size/2,SEEK_SET);
  
  while (read(in, &c, 1) == 1){
    write(out, &c, 1);
  }

return 0;
}