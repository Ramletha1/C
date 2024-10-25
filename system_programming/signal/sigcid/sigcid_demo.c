#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* one handler for both signals */
static void sig_usr(int);

int main(void) {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    perror("can't catch SIGUSR1");
  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    perror("can't catch SIGUSR2");
  if (signal(SIGINT, sig_usr) == SIG_ERR)
    perror("can't catch SIGINT");
  for (;;)
    pause();
}

/* argument is signal number */
static void sig_usr(int signo) {
  if (signo == 10)
    printf("received SIGUSR1\n");
  else if (signo == SIGUSR2)
    printf("received SIGUSR2\n");
  else
    printf("received signal %d\n", signo);
}

// ./sigcid_demo
// **Open 2nd terminal**
// ps -u
// kill -l
//kill -9 <PID for ./sigcid_demo>