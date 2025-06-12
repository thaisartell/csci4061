#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // argc :  number of command line arguments
    // argv[1]: executable name
    // argv[2] onwards: arguments of executable
    if(argc != 3) {
        printf("./p4.o <m> <n>");
        exit(-1);
    }
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    // memory allocation of 2D array
    int **matrix = (int **)malloc(sizeof(int *) * m);
    if(matrix == NULL){
        printf("Memory cannot be allocated. Exiting...");
        exit(-1);
    }
    for(int i = 0; i < m; i++){
        matrix[i] = (int *)malloc(sizeof(int) * n);
        if(matrix[i] == NULL){
            printf("Memory cannot be allocated. Exiting...");
            exit(-1);
        }
    }
    
    // assignment of 2D array
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            matrix[i][j] = i * j;
        }
    }

    // memory deallocation
    for(int i = 0; i < m; i++){
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;

    return 0;
}