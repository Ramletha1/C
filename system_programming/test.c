#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>

#define KEY 11235
#define MAX_MSG_SIZE 256

// Define a message structure
struct message {
    long msg_type;                  // Message type (must be > 0)
    char msg_text[MAX_MSG_SIZE];    // Message content
};

int main(int argc, char *argv[]) {
    int msgid;
    struct message msg;
    char input[MAX_MSG_SIZE] = "";

    // Ensure correct usage
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <1 or 2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create or connect to a message queue with the specified key
    msgid = msgget(KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Failed to create/connect to message queue");
        exit(EXIT_FAILURE);
    }

    // Fork a child process to handle receiving messages
    pid_t pid = fork();
    if (pid < 0) {
        perror("Forking failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child Process: Receiving messages
        while (1) {
            // Receive a message of type 1
            if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) {
                perror("Failed to receive message");
                exit(EXIT_FAILURE);
            }

            printf("Received: %s\n", msg.msg_text);

            // Check for "end chat" to terminate
            if (strcmp(msg.msg_text, "end chat") == 0) {
                break;
            }
        }
        // Exit the child process
        exit(EXIT_SUCCESS);
    } else {
        // Parent Process: Sending messages
        while (1) {
            // Read message from standard input
            printf("Enter message: ");
            fgets(input, MAX_MSG_SIZE, stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline

            // Prepare and send the message
            msg.msg_type = 1;
            strncpy(msg.msg_text, input, MAX_MSG_SIZE);
            if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
                perror("Failed to send message");
                exit(EXIT_FAILURE);
            }

            // Check for "end chat" to terminate
            if (strcmp(input, "end chat") == 0) {
                break;
            }
        }

        // Wait for the child process to finish
        wait(NULL);

        // Clean up the message queue if process "1" is ending the chat
        if (strcmp(argv[1], "1") == 0) {
            if (msgctl(msgid, IPC_RMID, NULL) == -1) {
                perror("Failed to delete message queue");
                exit(EXIT_FAILURE);
            }
        }

        printf("Chat ended.\n");
        exit(EXIT_SUCCESS);
    }
}
