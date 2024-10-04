#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
char block[512]; int in, out, nread;
in = open("file.in", O_RDONLY);
out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
while ((nread = read(in, block, sizeof(block))) > 0) write(out, block, nread);
return 0;
}