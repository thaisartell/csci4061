#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h> 

/*
    Fill the locations with ?
    There may be more modifications required.
    Expected output: The values could differ, however you will observe a similar trend.
        ./matrix.o 10000 1
        418.210000 ms.
        ./matrix.o 10000 2
        227.231000 ms.
        ./matrix.o 10000 4
        116.305000 ms.
        ./matrix.o 10000 8
        60.665000 ms.
*/

struct Arguments{
    int **matA;
    int **matB;
    int **matC;
    int m;
    int start_col;
    int end_col;
};

typedef struct Arguments Args;

void *matCequalmatAplusmatB(void *arg) {
    Args *targ = (Args *) arg;
    for(int i = 0; i < targ->m; i++) {
        for(int j = targ->start_col; j < targ->end_col; j++) {
            targ->matC[i][j] = targ->matA[i][j] + targ->matB[i][j];
        }
    }

    return NULL;
}

int **allocMat(int m){
    int **mat = (int **) malloc(sizeof(int *) * m);
    for(int i = 0; i < m; i++) {
        mat[i] = (int *) malloc (sizeof(int) * m);
    }

    return mat;
}

void freeMat(int **mat, int m) {
    for(int i = 0; i < m; i++) {
        free(mat[i]);
    }
    free(mat);
    mat = NULL;
}

int main(int argc, char *argv[]) {
    int m = atoi(argv[1]);// number of rows
    int t = atoi(argv[2]);// number of columns: THREADS

    int **matA = allocMat(m), **matB = allocMat(m), **matC = allocMat(m);

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            matA[i][j] = i + j;
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            matB[i][j] = i * j;
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            matC[i][j] = 0;
        }
    }

    int num_cols_per_thread = m / t;
    int extra  = m % t;

    Args args[t];
    int idx = 0;
    for(int i = 0; i < t; i++) {
        args[i].matA = matA;
        args[i].matB = matB;
        args[i].matC = matC;
        args[i].m = m;
        args[i].start_col = idx;
        args[i].end_col = num_cols_per_thread + idx;

        if (i == t - 1) { // last thread
            args[i].end_col = extra;
        }

        idx += num_cols_per_thread;
    }

    struct timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);

    pthread_t tid[t];
    // pthread_attr_t attr;

    for(int i = 0; i < t; i++) {
        // create threads
        pthread_create(&tid[i], NULL, matCequalmatAplusmatB, &args[i]);
    }

    int join;
    for(int i = 0; i < t; i++) {
        // join threads
        join = pthread_join(tid[i], NULL);
    }

     // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("%f ms.\n", elapsedTime);

    freeMat(matA, m);
    freeMat(matB, m);
    freeMat(matC, m);

    return 0;
}
