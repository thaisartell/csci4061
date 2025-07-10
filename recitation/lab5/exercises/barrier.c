#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // lock for critical section
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // condition variable for setting up barrier

int reached_barrier = 0; // variable to track if all threads reached the barrier

void barrier(int id) {
    // lock 
    pthread_mutex_lock(&mutex);
    printf("Thread %d reached barrier\n", id);
    reached_barrier++;

    if(reached_barrier == NTHREADS){ // You should first check if including the current thread, has every other thread reached the barrier
        printf("Thread %d broadcasting threads to cross barrier\n", id);
        // broadcast all the threads at the barrier to continue execution
        pthread_cond_broadcast(&cond);
    } else {
        // Wait for all threads to read the barrier
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Thread %d crossing barrier\n", id);
    // unlock 
    pthread_mutex_unlock(&mutex);
}

void *barrierfoo(void *args) {
    int id = *((int *)args);
    printf("Thread %d calling barrier\n", id);
    barrier(id);
    printf("Thread %d crossed barrier\n", id);
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t thds[NTHREADS];

    int thdids[NTHREADS];
    int ret = 0;
    for(int i = 0; i < NTHREADS; i++) {
        thdids[i] = i;
        ret = pthread_create(&thds[i], NULL, barrierfoo, &thdids[i]);
        if(ret != 0) {
            printf("Error creating thread %d\n", thdids[i]);
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < NTHREADS; i++) {
        ret = pthread_join(thds[i], NULL);
        if(ret != 0) {
            printf("Error joining thread %d\n", thdids[i]);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

/*

    Expected output: Order may change
    Thread 0 calling barrier
    Thread 0 reached barrier
    Thread 1 calling barrier
    Thread 1 reached barrier
    Thread 2 calling barrier
    Thread 2 reached barrier
    Thread 2 broadcasting threads to cross barrier
    Thread 2 crossing barrier
    Thread 2 crossed barrier
    Thread 0 crossing barrier
    Thread 0 crossed barrier
    Thread 1 crossing barrier
    Thread 1 crossed barrier
*/