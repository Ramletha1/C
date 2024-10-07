#include <pthread.h>
#include <stdio.h>
//Compute successive prime numbers (very inef ciently).
//Return the Nth prime number, where N is the value pointed to by *ARG.v

void* compute_prime (void* arg){
    int candidate = 2, n = *((int*) arg);
    while (1){
        int factor, is_prime = 1;
        /* Test primality by successive division. */
        for (factor = 2; factor < candidate; ++factor)
            if (candidate % factor == 0){
                is_prime = 0; break; 
            }
        /* Is this the prime number we’re looking for? */
        if (is_prime){
            if (--n == 0){
                /* Return the desired prime number as the thread return value. */
                return (void*) candidate;
            }
        }
        ++candidate;
    }
    return NULL;
}

int main (){
    pthread_t thread;
    int which_prime = 5133, prime;
    /* Start the computing thread, up to the 5,133th prime number. */
    pthread_create (&thread, NULL, &compute_prime, &which_prime);
    /* Do some other work here... */
    /* Wait for the prime number thread to complete, and get the result. */
    pthread_join (thread, (void*) &prime);
    /*Print the 5,133th prime it computed. */
    printf("The %dth prime number is %d.\n", which_prime, prime);
    
    return 0;
}