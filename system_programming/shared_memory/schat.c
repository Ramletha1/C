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

void signal_handler(int sig) {
  printf("\nChat terminated.\n");
  exit(0);
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
  struct share_memory *shm;
  signal(SIGINT, signal_handler);

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
  printf("Memory attached (%X)\n", shm_ptr); // just indicator

  shm = (struct share_memory *)shm_ptr;

  if (chat == 1) {
    shm->flag = 1;
    memset(shm->text, 0, BUFFER_SIZE);
  } /* else {
    shm->flag = 2;
  }*/

  printf("Chat started. Type 'end chat' to end program.\n");

  while (1) {
    if (shm->flag == chat) {
      printf("You: ");
      fgets(shm->text, BUFFER_SIZE, stdin);
      shm->text[strcspn(shm->text, "\n")] = '\0';
    }

    if (strcmp(shm->text, "end chat") == 0) {
      printf("You ended the chat.\n");
      shm->flag = 0;
      break;
    }
    
    shm->flag = (chat == 1) ? 2 : 1;
    // if (chat == 1) shm->flah = 2;
    // else shm->flag = 1;
    
    if (shm->flag == 0) {
      printf("Other side ended the chat.");
      break;
    } else {
      if (strlen(shm->text) > 0) {
        printf("\nReceived: %s\n", shm->text);
        memset(shm->text, 0, BUFFER_SIZE);
      }
      usleep(100000);
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