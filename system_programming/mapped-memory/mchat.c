#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFSIZE 0x100
struct mmap_struct *file_memory; // pointer to mapped memory structure
int FILE_LENGTH = 1024; //it has to be bigger than BUFSIZE

void signal_handler(int SIGNO){
  munmap(file_memory, FILE_LENGTH);
  system("rm -f chat_log");
  exit(0);
}
struct mmap_struct {
  int written1; 
  int written2;
  char msg1[BUFSIZE];
  char msg2[BUFSIZE];
};

int main(int argc, char *const argv[]) {
  char buffer[BUFSIZ];
  int fd;
  int nread,chat_log; //chat_log = fd for chat_log

  if (argc < 2) {
    fprintf(stderr, "Usage: %s User has to enter 1 or 2 as argv\n", *argv);
    exit(EXIT_FAILURE);
  }

  fd = open("./chat_log", O_RDWR | O_CREAT , S_IRUSR | S_IWUSR); //for mapped memory. because we want to know which user is sending msg. it needs synchronization 
  lseek(fd, FILE_LENGTH + 1, SEEK_SET);
  write(fd, "", 1); // specify the end of file
  lseek(fd, 0, SEEK_SET);

  //mapping memory (file "mapped" is shared between processes)
  file_memory = mmap(0, FILE_LENGTH, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
  //file memory struct points to mapped memory file (this is shared among processes)
  close(fd);
  
   argv++;
  // parent read from keyboard, child display and write in chat_log
  if (strcmp(*argv, "1") == 0) { // user 1
    pid_t pid = fork();

    if (pid == -1) {
      perror("Fork failed");
      exit(EXIT_FAILURE);
    } 
    else if (pid > 0) { // parent
      signal(SIGTERM,signal_handler);
      file_memory->written1 = 0;
      while (1) {
        if(strncmp(file_memory->msg1, "end chat", 8) == 0) break;
        // Wait until type is reset to 0
        if (file_memory->written1 == 0) 
        {
          fgets(buffer, BUFSIZE, stdin);
          file_memory->written1 = 1;
          strncpy(file_memory->msg1, buffer, BUFSIZE);
        }
        
      }
      sleep(1);
      kill(pid,SIGTERM);
      raise(SIGTERM);
    }
    else { // child

      while (1) {
        if(strncmp(file_memory->msg2, "end chat", 8) == 0) break;
        if (file_memory->written2 == 1) { 
          printf("%s", file_memory->msg2);
          file_memory->written2 = 0;
        }
        
      }
        sleep(1);
        kill(getppid(),SIGTERM);
        raise(SIGTERM);
      }
  } 
  
  else if (strcmp(*argv, "2") == 0) { // user 2
    pid_t pid = fork();
 
    if (pid == -1) {
      perror("Fork failed");
      exit(EXIT_FAILURE);
    } 
    else if (pid > 0) { // parent
      signal(SIGTERM,signal_handler);
      file_memory->written2 = 0;
  
      while (1) {
        // Wait until type is reset to 0
        if(strncmp(file_memory->msg2, "end chat", 8) == 0) break;
        if (file_memory->written2 == 0) 
        {
          fgets(buffer, BUFSIZE, stdin);
          file_memory->written2 = 1;
          strncpy(file_memory->msg2, buffer, BUFSIZE);
        }

      }
      sleep(1);
      kill(pid,SIGTERM);
      raise(SIGTERM);

    } 
    else { // child

      while (1) {
        if(strncmp(file_memory->msg1, "end chat", 8) == 0) break;
        if (file_memory->written1 == 1) {
          printf("%s", file_memory->msg1);
          file_memory->written1 = 0;
        }
        
      }
      sleep(1);
      kill(getppid(),SIGTERM);
      raise(SIGTERM);
   
    }
  }

  return 0;
}