// DEMO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>

#define SHM_KEY 21930
#define BUFFER_SIZE 1024

struct shared_memory {
    int turn;              // Indicates whose turn it is (1 or 2)
    char message[BUFFER_SIZE]; // Stores the message
};

pid_t pid; // Global process ID for managing forked processes

void terminate_chat(int signum) {
    printf("\nChat terminated.\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // Error handling for argument count
        fprintf(stderr, "Usage: %s <1 or 2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int process = atoi(argv[1]);
    if (process != 1 && process != 2) { // Error handling for invalid argument
        fprintf(stderr, "Argument must be 1 or 2\n");
        exit(EXIT_FAILURE);
    }

    // Create or access shared memory
    int shmid = shmget(SHM_KEY, sizeof(struct shared_memory), 0666 | IPC_CREAT);
    if (shmid == -1) { // Error handling for shared memory creation
        perror("Failed to create or access shared memory");
        exit(EXIT_FAILURE);
    }

    // Attach to shared memory
    struct shared_memory *shm = (struct shared_memory *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) { // Error handling for shared memory attachment
        perror("Failed to attach to shared memory");
        exit(EXIT_FAILURE);
    }

    // Initialize shared memory if process is 1
    if (process == 1) {
        shm->turn = 1; // Process 1 starts the conversation
        memset(shm->message, 0, BUFFER_SIZE); // Clear the message buffer
    }

    // Set up signal handler for termination (Ctrl+C)
    signal(SIGINT, terminate_chat);

    printf("Chat started. Type 'end chat' to quit.\n");

    // Chat loop
    while (1) {
        if (shm->turn == process) { // This process's turn to send
            printf("You: ");
            fgets(shm->message, BUFFER_SIZE, stdin);
            shm->message[strcspn(shm->message, "\n")] = 0; // Remove newline character

            if (strcmp(shm->message, "end chat") == 0) { // Check for termination
                printf("You have ended the chat.\n");
                shm->turn = 3 - process; // Pass turn to the other process
                break;
            }

            shm->turn = 3 - process; // Pass turn to the other process
        } else { // This process's turn to receive
            if (shm->turn == 0) { // Indicates chat termination
                printf("Other side has left the chat.\n");
                break;
            }

            if (strlen(shm->message) > 0) { // Wait until a message is written
                printf("\nReceived: %s\n", shm->message);
                memset(shm->message, 0, BUFFER_SIZE); // Clear the message after reading
            }
            usleep(100000); // Prevent busy-waiting
        }
    }

    // Cleanup for process 1
    if (process == 1) {
        shm->turn = 0; // Indicate termination
        if (shmdt(shm) == -1) {
            perror("Failed to detach shared memory");
        }
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("Failed to remove shared memory");
        }
        printf("Shared memory cleaned up.\n");
    } else { // Detach for process 2
        if (shmdt(shm) == -1) {
            perror("Failed to detach shared memory");
        }
    }

    printf("Chat ended.\n");
    return 0;
}
