#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// gcc main.c -o main -lpthread

// Argument (void *unused) doesn't mean no need argument. Instead, it can be anything.

void *print_Xs(void *unused){
    int n;
    for(n=100; n>0; n--){
        fputc('X', stderr);
        usleep(1);
    }
    return NULL;
}

void *print_Ys(void *unused){
    int n;
    for(n=100; n>0; n--){
        fputc('Y', stderr);
        usleep(1);
    }
    return NULL;
}

int main(){
    int n;
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, &print_Xs, NULL);
    pthread_create(&thread_id, NULL, &print_Ys, NULL);

    for(n=100; n>0; n--){
        fputc('Z',stderr);
        usleep(1);
    }
    usleep(1000000);
    return 0;
}