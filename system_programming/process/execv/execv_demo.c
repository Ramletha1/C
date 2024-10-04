#include <stdio.h>
#include <unistd.h>

int main(){
    char* argv1[] = {"print","1","10",NULL};
    char* argv2[] = {"print","2","20",NULL};
    pid_t pid = fork();

    //printf("Process ID: %d\n",pid);
    if(pid == 0){   // For child process
        printf("Process ID: %d\n",pid);
        execv("./print",argv1);
        printf("This is child.\n");
        // Terminate this process and return exit status
    }
    else{           // For Parent Process
        // Suspend parent until child process terminate
        printf("Process ID: %d\n",pid);
        execv("./print",argv2);
        printf("This is parent.\n");
    }
}

// wait() and _exit(0) allow program concurrency