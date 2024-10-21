#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void my_alarm(int sig) {
    for (int i = 0; i < 5; i++) printf("Alarm!!! \n");
}

int main(void) {
    int pid;
  
    printf("Alarm clock is starting...\n");

    /*
    if ((pid = fork()) == 0) {
        sleep(3);
        kill(getppid(), SIGALRM);
        _exit(0);
    }
    */
  
    printf("Waiting for alarm...\n");
    signal(SIGALRM, my_alarm);
    pause();
    printf("Done!\n");
    _exit(0);
}