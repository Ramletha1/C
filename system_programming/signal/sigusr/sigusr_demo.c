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
    for (;;)
        pause();
}

/* argument is signal number */
static void sig_usr(int signo) {
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        printf("received signal %d\n", signo);
}

// While code is running

// Nothing will appear

// Add another shell or terminal and do ps -u

// kill -l