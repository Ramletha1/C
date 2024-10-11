#include <pthread.h>
#include <stdio.h>
//Compute successive prime numbers (very inef ciently).
//Return the Nth prime number, where N is the value pointed to by *ARG.v

#define MAX_NUMBER 50000
#define MAX_THREAD 5

typedef struct {
    int start;
    int end;
    int* primes;
    int* count;
} ThreadArgs;

void* compute_prime (void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;
    int start = args->start;
    int end = args->end;
    int* primes = args->primes;
    int* count = args->count;

    for (int candidate = start; candidate<end; candidate++) {
        if (candidate<2) continue;
        //.......
    }
}

int main () {
    pthread_t thread[MAX_THREAD];
    ThreadArgs thread_args[MAX_THREAD];
    int* primes = malloc(sizeof(int) * MAX_NUMBER);
    int prime_count = 0;

    for(int count=0; count<MAX_THREAD; count++) {
        thread_args[i].start = (MAX_NUMBER/MAX_THREAD) * count;
        thread_args[i].end = (MAX_NUMBER/MAX_THREAD) + thread_args[i].start;
        thread_args[i].primes = primes;
        thread_args[i].count = &prime_count;
        pthread_create(&thread[i], NULL, compute_prime, thread_args[i]);
    }

    for(int count=0; count<MAX_THREAD; count++) {
        pthread_join(&thread[i], NULL);
    }
    
    printf("Printing all prime number from 0 to %d.\n", MAX_NUMBER);
    for(int count=0; count<prime_count; count++) {
        printf("%d\n", primes[count]);
    }

    return 0;
}