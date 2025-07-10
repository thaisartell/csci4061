#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // lock for critical section
pthread_cond_t wait_cons = PTHREAD_COND_INITIALIZER; // cv used by producer to wait on consumer and used by producer to signal producer
pthread_cond_t wait_prod = PTHREAD_COND_INITIALIZER; // cv used by consumer to wait on producer and used by consumer to signal consumer

// use consumed variable to control the transfer of control between producer and consumer
// producer will set consumed to 0, if it has produced an item
// consumer will set consumed to 1, if it has consumed an item
int consumed = 1; 

// producer thread
void *producer(void *args) {
    int total_produced = 0; // tracks the number of items produced
    while(total_produced < 5){ // exit when number of items produced is 5
        // lock?
        pthread_mutex_lock(&mutex);

        while(consumed == 0) {// condition expression using consumed
            // wait for a signal from consumer saying it has consumed the produced item. Hint: use wait_cons
            pthread_cond_wait(&wait_cons, &mutex);
        }
        printf("Producer produced an item for consumer consumption\n");
        total_produced++;
        // change consumed and signal consumer about availability of an item. Hint use wait_prod
        consumed = 0;
        pthread_cond_signal(&wait_prod);
        // unlock ?
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// consumer thread
void *consumer(void *args) {
    int total_consumed = 0; // tracks the number of items consumed
    while(total_consumed < 5){ // exit when number of items consumed is 5
        // lock ?
        pthread_mutex_lock(&mutex);

        while(consumed == 1) {// condition expression using consumed
            // wait for a signal from producer saying it has produced an item for consumption. Hint: wait_prod 
            pthread_cond_wait(&wait_prod, &mutex);
        }
        printf("Consumer consumed item produced by producer\n");
        total_consumed++;
        // change consumed and signal producer about unavailability of an item to consume. Hint: use wait_cons
        consumed = 1;
        pthread_cond_signal(&wait_cons);
        // unlock ?
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[]) {
    pthread_t prodthd, consthd;
    
    int ret = pthread_create(&prodthd, NULL, producer, NULL);
    if(ret != 0) {
        printf("Error creating producer thread\n");
        exit(EXIT_FAILURE);
    }
    ret = pthread_create(&consthd, NULL, consumer, NULL);
    if(ret != 0) {
        printf("Error creating consumer thread\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_join(prodthd, NULL);
    if(ret != 0) {
        printf("Error joining producer thread\n");
        exit(EXIT_FAILURE);
    }
    ret = pthread_join(consthd, NULL);
    if(ret != 0) {
        printf("Error joining consumer thread\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*
    Expected output:
    Producer produced an item for consumer consumption
    Consumer consumed item produced by producer
    Producer produced an item for consumer consumption
    Consumer consumed item produced by producer
    Producer produced an item for consumer consumption
    Consumer consumed item produced by producer
    Producer produced an item for consumer consumption
    Consumer consumed item produced by producer
    Producer produced an item for consumer consumption
    Consumer consumed item produced by producer
*/