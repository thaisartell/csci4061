#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Usage: ./p3.o <number of child processes>");
        exit(EXIT_FAILURE);
    }
    /*
        Prints hierarchy of processes. Total number of processes will be main process + number of child processes
        make runs the code with number of child processes  = 5, so total number of processes  = main + 5 = 6
        
        main -> 1 -> 2 -> 3 -> 4 -> 5
        main creates 1 creates 2 creates 3 creates 4 creates 5
        Each process will wait for its child to complete
        Note the way in which the print occurs 0 1 2 3 4 5. Try to print it the other way, i.e., 5 4 3 2 1 0
    */

    int n = atoi(argv[1]);

    // hierarchy of processes
    int i;
    printf("main 0: %d\n", getpid());
    for(i = 0; i < n; i++) {
        int pid = fork();   // create parent, child
        if(pid == 0){       // if child, print pid of child at level (i + 1)
            printf("pid %d: %d\n", i + 1, getpid());
            continue;
        }else   // if parent, quit
            break;
    }
    if(i != n){ // wait will return -1 for the last process as there is no one to wait for
        int pid = wait(NULL); // wait for child
        if(pid == -1){
            printf("ERROR: Process %d failed waiting\n", getpid());
            exit(EXIT_FAILURE);
        } else {
            printf("Process %d completed wait for child %d\n", getpid(), pid);
        }
    }

    return 0;
}