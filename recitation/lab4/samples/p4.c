// Race condition

#include <stdio.h>
#include <pthread.h>

void *display(void *arg){
    int *data = (int *)arg;
    for(int i = 1; i < 1000; i++)
        (*data) = (*data) + i;
}

int main(int argc, char *argv[]){
    pthread_t arg1_thread;
    pthread_t arg2_thread;

    int shared_variable = 1;

    // create two threads
    pthread_create(&arg1_thread, NULL, (void*)display, (void*)&shared_variable);
    pthread_create(&arg2_thread, NULL, (void*)display, (void*)&shared_variable);

    // join the two threads
    pthread_join(arg1_thread, NULL);
    pthread_join(arg2_thread, NULL);

    printf("Shared variable: %d\n", shared_variable);

    return 0;
}