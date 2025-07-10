#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *t1_foo(void *arg) {
    int *x = (int *)arg;
    
    int ret = pthread_mutex_lock(&mutex); 
    if(ret != 0){
        printf("Error locking thread 1\n");
        exit(EXIT_FAILURE);
    }
    while(*(x) != 1){
        printf("Thread 1 waiting for x to be 1\n");
        ret = pthread_cond_wait(&cond, &mutex);
        if(ret != 0){
            printf("Error waiting thread 1\n");
            exit(EXIT_FAILURE);
        }
        printf("Thread 1 rechecking if x == 1\n");
    }
    (*x)++;
    printf("Thread 1 value of x: %d\n", *x);
    ret = pthread_mutex_unlock(&mutex);
    if(ret != 0){
        printf("Error unlocking thread 1\n");
        exit(EXIT_FAILURE);
    }

    return NULL;
}

void *t2_foo(void *arg) {
    int *x = (int *)arg;


    int ret = pthread_mutex_lock(&mutex);
    if(ret != 0){
        printf("Error locking thread 2\n");
        exit(EXIT_FAILURE);
    }
    printf("Thread 2 changing value of x to 1\n");
    *x = 1;
    ret = pthread_cond_signal(&cond);
    if(ret != 0){
        printf("Error signaling thread 2\n");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_unlock(&mutex);
    if(ret != 0){
        printf("Error unlocking thread 2\n");
        exit(EXIT_FAILURE);
    }
    
    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t thd[2];

    int val = 0;

    int ret = pthread_create(&thd[0], NULL, t1_foo, &val);
    if(ret != 0){
        printf("Error creating thread 1\n");
        exit(EXIT_FAILURE);
    }
    ret = pthread_create(&thd[1], NULL, t2_foo, &val);
    if(ret != 0){
        printf("Error creating thread 2\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_join(thd[0], NULL);
    if(ret != 0){
        printf("Error joining thread 1\n");
        exit(EXIT_FAILURE);
    }
    ret = pthread_join(thd[1], NULL);
    if(ret != 0){
        printf("Error joining thread 2\n");
        exit(EXIT_FAILURE);
    }
    printf("Value: %d\n", val);

    return 0;

}