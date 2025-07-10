#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct Arguments {
    int id;
    int *val;
};

typedef struct Arguments Args;

void *waitingfoo(void *arg) {
    Args *thdinfo = (Args *)arg;
    
    int ret = pthread_mutex_lock(&mutex); 
    if(ret != 0){
        printf("Error locking thread %d\n", thdinfo->id);
        exit(EXIT_FAILURE);
    }
    while(*(thdinfo->val) == 0){
        printf("Thread %d waiting for val to be 1\n", thdinfo->id);
        ret = pthread_cond_wait(&cond, &mutex);
        if(ret != 0){
            printf("Error waiting thread %d\n", thdinfo->id);
            exit(EXIT_FAILURE);
        }
        printf("Thread %d rechecking if val == 1\n", thdinfo->id);
    }
    (*thdinfo->val)++;
    printf("Thread %d value of val: %d\n", thdinfo->id, *(thdinfo->val));
    ret = pthread_mutex_unlock(&mutex);
    if(ret != 0){
        printf("Error unlocking thread %d\n", thdinfo->id);
        exit(EXIT_FAILURE);
    }

    return NULL;
}

void *signalingfoo(void *arg) {
    Args *thdinfo = (Args *)arg;


    int ret = pthread_mutex_lock(&mutex);
    if(ret != 0){
        printf("Error locking thread %d\n", thdinfo->id);
        exit(EXIT_FAILURE);
    }
    printf("Thread %d changing value of val to 1\n", thdinfo->id);
    *(thdinfo->val) = 1;
    ret = pthread_cond_broadcast(&cond);
    if(ret != 0){
        printf("Error signaling thread %d\n", thdinfo->id);
        exit(EXIT_FAILURE);
    }
    pthread_mutex_unlock(&mutex);
    if(ret != 0){
        printf("Error unlocking thread %d\n", thdinfo->id);
        exit(EXIT_FAILURE);
    }
    
    return NULL;
}

int main(int argc, char *argv[]) {

    int x = 0;

    pthread_t waitThd[5];
    Args waitArgs[5];

    pthread_t signalThd;
    Args signalArgs;

    for(int i = 0; i < 5; i++){
        waitArgs[i].id = i;
        waitArgs[i].val = &x;
        int ret = pthread_create(&waitThd[i], NULL, waitingfoo, &waitArgs[i]);
        if(ret != 0){
            printf("Error creating waiting thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    signalArgs.id = 5;
    signalArgs.val = &x;
    int ret = pthread_create(&signalThd, NULL, signalingfoo, &signalArgs);
    if(ret != 0){
        printf("Error creating waiting thread %d\n", signalArgs.id);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 5; i++){
        int ret = pthread_join(waitThd[i], NULL);
        if(ret != 0) {
            printf("Error joining waiting thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    ret = pthread_join(signalThd, NULL);
    if(ret != 0) {
        printf("Error joining waiting thread %d\n", signalArgs.id);
        exit(EXIT_FAILURE);
    }

    printf("Value is %d\n", x);

    return 0;
}