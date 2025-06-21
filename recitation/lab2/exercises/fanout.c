#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Usage: ./fanout.o <number of child processes>\n");
        exit(EXIT_FAILURE);
    }
    /*
        Fan out for the main process. Total number of processes will be main process + number of child processes
        make runs the code with number of child processes  = 5, so total number of processes  = main + 5 = 6
        
        main
            -> 1
            -> 2
            -> 3
            -> 4
            -> 5
        main creates 1, 2, 3, 4, 5
        main will wait for all of its children to complete execution
    */

   /*
        The numerical values will change. Add print statements that follow the output given below.
        Expected output:
        main 0: 24753
        24753 created 24754
        24753 created 24755
        24753 created 24756
        24753 created 24757
        24753 created 24758
        24753 completed wait for 24754
        24753 completed wait for 24755
        24753 completed wait for 24756
        24753 completed wait for 24757
        24753 completed wait for 24758
   */

    int n = atoi(argv[1]);

    int i;
    printf("main 0: %d\n", getpid());
    // You may need to store the main process pid for later use
    for(i = 0; i < n; i++) {
        // Refer to samples/p3.c before completing this exercise. Understand it well. You should be able to solve it
        // based the logic given there.
        // The will be a change in the if else code of samples/p3.c
        int status = (int)fork();

        if (status < 0) {   // error
            exit(EXIT_FAILURE);
        }
        else if (status == 0) { // child created
            printf("Process %d created %d\n", getppid(), getpid());
            exit(0);
        }
    }

    int j;
    for (j = 0; j < n; j++){ // wait will return -1 for the last process as there is no one to wait for
        int pid = wait(NULL); // wait for child
        if(pid == -1) {
            printf("ERROR: Process %d failed waiting\n", getpid());
            exit(EXIT_FAILURE);
        } else {
            printf("Process %d completed wait for child %d\n", getpid(), pid);
        }
    }

    return 0;
}