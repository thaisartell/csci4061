#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *syncfoo(void *arg) {
    int *val = (int *)arg;
    for(int i = 0; i < 100000; i++){
        pthread_mutex_lock(&mutex);
        (*val)++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t thd[2];

    int val = 0;

    pthread_create(&thd[0], NULL, syncfoo, &val);
    pthread_create(&thd[1], NULL, syncfoo, &val);

    pthread_join(thd[0], NULL);
    pthread_join(thd[1], NULL);

    printf("Value: %d\n", val);

    return 0;

}