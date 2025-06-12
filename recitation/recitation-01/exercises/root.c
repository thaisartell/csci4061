#include "dep1.h"
#include "dep2.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int m = 5;

    int *arr1 = (int *)malloc(sizeof(int) * m), *arr2 = (int *)malloc(sizeof(int) * m);

    for(int i = 0; i < m; i++) {
        arr1[i] = i;
        arr2[i] = i + i;
    }

    printf("Dependency 1: %d\n", sumres(arr1, arr2, m));
    printf("Dependency 2: %d\n", pdtres(arr1, arr2, m));

    return 0;
}