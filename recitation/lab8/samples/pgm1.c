#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*
    loop variable set to 0

    ctrlHandler is the signal handler for Ctrl + C (SIGINT)

    The signal handler is first installed

    Anything during the program execution, if Ctrl + C is used, the program will gracefully exit instead of abrupt exit.
*/
int loop = 0;

void ctrlHandler(int signo) {
    printf("\nLoop var set\n");
    fflush(stdout);
    loop = 1;
}

int main(int argc, char *argv[]) {

    struct sigaction action;
    action.sa_handler = ctrlHandler; // handler for SIGINT
    action.sa_flags = 0; // no flags set

    if((sigemptyset(&action.sa_mask) == -1) || // check if mask is empty
        (sigaction(SIGINT, &action, NULL) == -1)) // add SIGINT to action
            perror("ERROR: Failure to set signal handler for Ctrl + C\n");
    
    int counter = 0;
    while(!loop) {
        printf("Counter: %d\n", counter++);
        fflush(stdout);
        sleep(1);
    }

    printf("Graceful exit\n");
    fflush(stdout);

    return 0;
}