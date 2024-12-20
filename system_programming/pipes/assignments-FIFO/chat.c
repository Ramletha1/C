#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_1 "./fifo1to2"
#define FIFO_2 "./fifo2to1"
#define MAX_RBUF 256



int FIFO_FD1, FIFO_FD2;

int main(int argc, char *argv[]) {
    int child, nbytes;
    char rbuf[MAX_RBUF] = "";
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <[1, 2]>\n", *argv);
        exit(EXIT_FAILURE);
    }
    
    if (access(FIFO_1, F_OK) == -1) {
        FIFO_FD1 = mkfifo(FIFO_1, 0777);
        if (FIFO_FD1) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_1);
            exit(EXIT_FAILURE);
        }
    }

    if (access(FIFO_2, F_OK) == -1) {
        FIFO_FD2 = mkfifo(FIFO_2, 0777);
        if (FIFO_FD2) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_2);
            exit(EXIT_FAILURE);
        }
    }
    ////////////////////////////////////////////////////
    // FIFO_FD1 = open(FIFO_1, O_WRONLY);
    // FIFO_FD2 = open(FIFO_2, O_RDONLY);
    argv++;
    if (strcmp(*argv, "1") == 0) {  // First Terminal
        FIFO_FD1 = open(FIFO_1, O_WRONLY);
        FIFO_FD2 = open(FIFO_2, O_RDONLY);
        child = fork();
        switch (child) {
            case -1: 
                perror("Forking failed"); 
                exit(EXIT_FAILURE);
            case 0: // CHILD PROCESS = READ
                while (strncmp(rbuf, "end chat", 8)) {
                    // CODE HERE //
                    memset(rbuf, 0, MAX_RBUF);
                    nbytes = read(FIFO_FD2, rbuf, MAX_RBUF);
                    if (nbytes>0) {
                        printf("Received: %s", rbuf);
                    }
                }
                break;
            default: // PARENT PROCESS = WRITE
                while (strncmp(rbuf, "end chat", 8)) {
                    // CODE HERE //
                    memset(rbuf, 0, MAX_RBUF);
                    fgets(rbuf, MAX_RBUF, stdin);   // step 1: read from stdin at terminal 1
                    write(FIFO_FD1, rbuf, strlen(rbuf) + 1); // step 2: write to FIFO_FD1
                }
        }
    }
    else if (strcmp(*argv, "2") == 0) { // Second Terminal
        FIFO_FD1 = open(FIFO_1, O_RDONLY);
        FIFO_FD2 = open(FIFO_2, O_WRONLY);
        child = fork();
        switch (child) {    // Mirror from Terminal 1
            case -1:
                perror("Forking failed");
                exit(EXIT_FAILURE);
            case 0: // CHILD PROCESS = READ
                while (strncmp(rbuf, "end chat", 8)) {
                    // CODE HERE //
                    memset(rbuf, 0, MAX_RBUF);
                    nbytes = read(FIFO_FD1, rbuf, MAX_RBUF); // step 3: read from FIFO_FD1
                    if (nbytes>0) {
                        printf("Received: %s", rbuf); // step 4: display at terminal 2
                    }
                }
                break;
            default: // PARENT PROCESS = WRITE
                while (strncmp(rbuf, "end chat", 8)) {
                    // CODE HERE //
                    memset(rbuf, 0, MAX_RBUF);
                    fgets(rbuf, MAX_RBUF, stdin);
                    write(FIFO_FD2, rbuf, strlen(rbuf) + 1);
                }
        }
    }
    ////////////////////////////////////////////////////
    if (FIFO_FD1 != -1) close(FIFO_FD1);
    if (FIFO_FD2 != -1) close(FIFO_FD2);
    exit(EXIT_SUCCESS);
}