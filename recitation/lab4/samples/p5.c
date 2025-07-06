// Voiding race condition for two threads

#include <stdio.h>
#include <pthread.h>

int flag = 0;

struct Arguments{
    int id;
    int *variable;
};

typedef struct Arguments Args;


void *display(void *arg){
    Args *data = (Args *)arg;
    int id = data->id;
    for(int i = 1; i < 1000; i++){
        while(flag != id); // busy waiting
        (*data->variable) = (*data->variable) + i;
        flag = !flag;
    }
}

int main(int argc, char *argv[]){
    pthread_t arg1_thread;
    pthread_t arg2_thread;

    int shared_variable = 1;

    // create two threads
    Args args[2];
    args[0].id = 0;
    args[0].variable = &shared_variable;
    args[1].id = 1;
    args[1].variable = &shared_variable;

    pthread_create(&arg1_thread, NULL, (void*)display, (void*)&args[0]);
    pthread_create(&arg2_thread, NULL, (void*)display, (void*)&args[1]);

    // join the two threads
    pthread_join(arg1_thread, NULL);
    pthread_join(arg2_thread, NULL);

    printf("Shared variable: %d\n", shared_variable);

    return 0;
}