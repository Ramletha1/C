#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER 50000
#define TOTAL_THREAD 5
#define PRINT_ALL true

typedef struct {
    int start;
    int end;
    int* local_primes;
    int local_count;
} ThreadArgs;

// pthread_mutex_t shared_resource;

void* compute_prime (void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;
    int start = args->start;
    int end = args->end;
    int* primes = args->local_primes;
    int count = 0;

    for (int candidate = start; candidate<=end; candidate++) {
        if (candidate<2) continue;
        bool is_prime = true;       // is prime

        for (int i = 2; i * i <= candidate; i++) {
            if (candidate % i == 0) {
                is_prime = false;   // not prime
                break;
            }
        }

        if (is_prime) {
            primes[count++] = candidate;
        }
    }
    args->local_count = count;
    return NULL;
}

int main () {
    pthread_t thread[TOTAL_THREAD];
    ThreadArgs thread_args[TOTAL_THREAD];
    int* primes = malloc(sizeof(int) * NUMBER);

    // pthread_mutex_init(&shared_resource, NULL);

    for (int i=0; i<TOTAL_THREAD; i++) {
        thread_args[i].start = (NUMBER/TOTAL_THREAD) * i;
        thread_args[i].local_primes = malloc(sizeof(int) * (NUMBER/TOTAL_THREAD));
        thread_args[i].local_count = 0;
        if (i == TOTAL_THREAD - 1) { thread_args[i].end = NUMBER; }
        else { thread_args[i].end = (NUMBER/TOTAL_THREAD) * (i + 1) - 1; }

        pthread_create(&thread[i], NULL, compute_prime, &thread_args[i]);
    }

    for (int i=0; i<TOTAL_THREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    int prime_count = 0;
    for (int i=0; i<TOTAL_THREAD; i++) {
        // pthread_lock(&shared_resource);
        for (int j=0; j < thread_args[i].local_count; j++) {
            primes[prime_count++] = thread_args[i].local_primes[j];
        }
        // pthread_unlock(&shared_resoruce);
        free(thread_args[i].local_primes);
    }
    
    if (PRINT_ALL) {
        for (int i=0; i<prime_count; i++) { printf(" %d", primes[i]); }
    }
    else {
        for (int i=0; i<5; i++) { printf(" %d", primes[i]); }
        printf(" ...");
        for (int i=prime_count-5; i<prime_count; i++) { printf(" %d", primes[i]); }
    }
    printf("\nTotal prime count is %d.\n", prime_count);

    // pthread_mutex_destroy(&shared_resource);
    free(primes);   // free allocated memory
    return 0;
}