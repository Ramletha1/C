#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>      
#include <sys/wait.h>   
#include <errno.h>
#include <string.h>

// Define semaphore names
#define SEM1_NAME "/s1_sem_example"
#define SEM2_NAME "/s2_sem_example"

sem_t *s1, *s2;

void f1() {
    printf("Function f1: Locked by Parent Process\n");
    sleep(1); 
}

void f2() {
    printf("Function f2: Locked by Child Process\n");
    sleep(1);
}

void parent_process() {
    // Parent locks s1
    if (sem_wait(s1) == -1) {
        perror("sem_wait s1 failed");
        exit(EXIT_FAILURE);
    }
    f1();

    printf("Parent process: Trying to lock f2\n");
    // Parent tries to lock s2
    if (sem_wait(s2) == -1) {
        perror("sem_wait s2 failed");
        sem_post(s1); // Release s1 before exiting
        exit(EXIT_FAILURE);
    }
    f2();

    printf("Done!\n");

    // Release semaphores
    if (sem_post(s2) == -1) {
        perror("sem_post s2 failed");
    }
    if (sem_post(s1) == -1) {
        perror("sem_post s1 failed");
    }
}

void child_process() {
    // Child locks s2
    if (sem_wait(s2) == -1) {
        perror("sem_wait s2 failed");
        exit(EXIT_FAILURE);
    }
    f2();

    printf("Child process: Trying to lock f1\n");
    // Child tries to lock s1
    if (sem_wait(s1) == -1) {
        perror("sem_wait s1 failed");
        sem_post(s2); // Release s2 before exiting
        exit(EXIT_FAILURE);
    }
    f1();

    printf("Done!\n");

    // Release semaphores
    if (sem_post(s1) == -1) {
        perror("sem_post s1 failed");
    }
    if (sem_post(s2) == -1) {
        perror("sem_post s2 failed");
    }
}

int main() {

    // Open (and create) semaphores with initial value of 1
    s1 = sem_open(SEM1_NAME, O_CREAT | O_EXCL, 0644, 1);
    if (s1 == SEM_FAILED) {
        perror("sem_open s1 failed");
        exit(EXIT_FAILURE);
    }

    s2 = sem_open(SEM2_NAME, O_CREAT | O_EXCL, 0644, 1);
    if (s2 == SEM_FAILED) {
        perror("sem_open s2 failed");
        sem_close(s1);
        sem_unlink(SEM1_NAME);
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        // Cleanup
        sem_close(s1);
        sem_close(s2);
        sem_unlink(SEM1_NAME);
        sem_unlink(SEM2_NAME);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        // Child process
        child_process();
        // Close semaphores in child
        sem_close(s1);
        sem_close(s2);
        exit(EXIT_SUCCESS);
    } else { 
        parent_process();
        wait(NULL);
        sem_close(s1);
        sem_close(s2);
        sem_unlink(SEM1_NAME);
        sem_unlink(SEM2_NAME);
    }

    return 0;
}
