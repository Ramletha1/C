// Made by Wongsatorn Suwannarit 6581167

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_KEY 21930
#define BUFFER_SIZE 1024

struct share_memory {
  int flag;
  char text[BUFFER_SIZE];
};

struct share_memory *shm;

void signal_handler(int sig) {
  if      (sig == 10) shm->flag = 1;    // 10 = SIGUSR1
  else if (sig == 12) shm->flag = 2;    // 12 = SIGUSR2
  else if (sig == 1)  shm->flag = -1;   // 1 = SIGHUP
  else if (sig == 2)  exit(0);          // 2 = SIGINT
}

int main(int argc, char *argv[]) {

  if (argc != 2) { // argc count == 2 only
    printf("Usage: %s <1 or 2>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int chat = atoi(argv[1]);     // process/chat number
  if (chat != 1 && chat != 2) { // argv == 1,2 only
    printf("Argument can be only 1 and 2\n");
    exit(EXIT_FAILURE);
  }

  key_t key = SHM_KEY;
  int shmID;
  void *shm_ptr = NULL;
  // struct share_memory *shm;
  signal(SIGHUP, signal_handler);   // SIGHUP  = 1
  signal(SIGINT, signal_handler);   // SIGINT  = 2
  signal(SIGUSR1, signal_handler);  // SIGUSR1 = 10
  signal(SIGUSR2, signal_handler);  // SIGUSR2 = 12

  shmID = shmget(key, sizeof(struct share_memory), 0666 | IPC_CREAT); // get shared memory ID
  if (shmID == -1) {                // failed to get shared memory ID
    perror("shmget Failed.");
    exit(EXIT_FAILURE);
  }

  shm_ptr = shmat(shmID, NULL, 0); // attach to shared memory
  if (shm_ptr == (void *)-1) {     // failed to attach
    perror("shmat Failed.");
    exit(EXIT_FAILURE);
  }
  // printf("Memory attached (%X)\n", shm_ptr); // just indicator

  shm = (struct share_memory *)shm_ptr;
  shm->flag = 0;

  printf("Chat started. Type 'end chat' to end program.\n");

  pid_t pid = fork();

  if (pid == 0) {       // Child
    while (1) {
      if (strcmp(shm->text, "end chat") == 0) {
        killpg(getpgid(0), SIGINT);
        printf("Chat terminated");
        break;
      }
      else if (strlen(shm->text) > 0 && shm->flag != chat) {
        printf("Received: %s\n", shm->text);
        memset(shm->text, 0, BUFFER_SIZE);
        shm->flag = 0;
      }
    }
  }
  else if (pid > 0) {   // Parent
    while (1) {
      if (shm->flag == 0) {
        if (chat == 1) {
          // printf("You: ");
          fgets(shm->text, BUFFER_SIZE, stdin);
          shm->text[strcspn(shm->text, "\n")] = '\0';
          if (strcmp(shm->text, "end chat") == 0) {
            killpg(getpgid(0), SIGINT);
            printf("Chat terminated");
            break;
          }
          kill(getpid(), SIGUSR1);
        }
        else if (chat == 2) {
          // printf("You: ");
          fgets(shm->text, BUFFER_SIZE, stdin);
          shm->text[strcspn(shm->text, "\n")] = '\0';
          if (strcmp(shm->text, "end chat") == 0) {
            killpg(getpgid(0), SIGINT);
            printf("Chat terminated");
            break;
          }
          kill(getpid(), SIGUSR2);
        }
      }
    }
  }

  if (shmdt(shm_ptr) == -1) {  // shared memory detach
    printf("shmdt Failed.");
    exit(EXIT_FAILURE);
  }

  if (chat == 1) {  // main chat (1)
    if (shmctl(shmID, IPC_RMID, NULL) == -1) {  // shared memory control
      printf("shmctl Failed.");
    } else {
      printf("Share memory cleaned up.\n");
    }
  }
}