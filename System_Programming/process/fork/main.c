#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid; char *msg; int n;

  printf("fork program starting\n");
  pid = fork();

  switch(pid)
  {
    case -1:
      _exit(1);
    case 0:
      msg = "Child!\n";
      n = 45;
      break;
    default:
      msg = "Parent!\n";
      n = 3; break;
  }
}
  
  /*for (; n>0; n--){
    puts(msg); sleep(1);
  }
  
  if (pid){
    int stat_val; pid_t child_pid;
    child_pid = wait(&stat_val);
    printf("Child has nished: PID = %d\n", child_pid);
    if (WIFEXITED(stat_val))
      printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
    else
      printf("Child terminated abnormally\n");
  }
  _exit(0);
}*/