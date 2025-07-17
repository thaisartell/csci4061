/*
    IMPORTANT: 
        Complete the code as per the instructions. There might be some other modifications required as well.
        You should understand Dining Philosophers Problem and its solution before starting to solve the code.
        Check all the global variables defined
        Error checking is not provided for pthread APIs in the code. However, when you code for project, you should have error checking.

        Use the deliver target to zip the deliverables
        Check the redirection (>) in philo target. Always clean the code before re-running.
*/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define LEFT(i) ((i - 1) + N) % N
#define RIGHT(i) (i + 1) % N

int nturns = 3; // Maximum number of times a philosopher eats

enum PSTATE {
    THINKING,
    HUNGRY,
    EATING
};

enum PSTATE state[N]; // stores current state of N philosophers

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // critical section lock
pthread_cond_t cond[N] = {PTHREAD_COND_INITIALIZER}; // condition variables for N philosophers

void acquireForks(int i) {
    int left = LEFT(i); // left philosopher id
    int right = RIGHT(i); // right philosopher id

    // add locking as required ????
    pthread_mutex_lock(&mutex);
    printf("Philosopher %d HUNGRY\n", i);
    // set state of philosopher
    while((state[left] == EATING) || (state[right] == EATING)) { // Check if the left and right philosophers are not eating
        printf("Philosopher %d HUNGRY and waiting for forks\n", i);
        // wait for signal from left/right philosopher
        pthread_cond_wait(&cond[i], &mutex);
    }

    printf("Philosopher %d ready to eat\n", i);
    // set state of philosopher//
    state[i] = EATING;

    pthread_mutex_unlock(&mutex);
}

void releaseForks(int i) {
    int left = LEFT(i); // left philosopher id
    int right = RIGHT(i); // right philosopher id

    // add locking as required
    pthread_mutex_lock(&mutex);

    // set state of philosopher
    state[i] = THINKING;
    
    // signal left and right philosophers about the availability of forks
    printf("Philosopher %d released left fork\n", i);
    pthread_cond_signal(&cond[left]);

    printf("Philosopher %d released right fork\n", i);
    pthread_cond_signal(&cond[right]);

    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg) {
    int philosopher_id = *((int *) arg);
    int myturn = 0;
    while (myturn < nturns) {
        // think()
        // set philosopher state ????
        printf("Philosopher %d THINKING\n", philosopher_id);
        state[philosopher_id] = THINKING;
        sleep(1);

        // acquireForks(i)
        acquireForks(philosopher_id);

        // eat()
        printf("Philosopher %d EATING\n", philosopher_id);
        sleep(1);

        // releaseForks();
        releaseForks(philosopher_id);
        myturn++;
    }
    printf("Philosopher %d finished its turns. Leaving table...\n", philosopher_id);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t philosopher_thd[N];

    int philosopher_id[N];
    for(int i = 0; i < N; i++){
        philosopher_id[i] = i;
        pthread_create(&philosopher_thd[i], NULL, philosopher, &philosopher_id[i]);
    }

    for(int i = 0; i < N; i++) {
        pthread_join(philosopher_thd[i], NULL);
    }

    return 0;

}