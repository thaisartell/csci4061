#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int loop = 0;

void ctrlHandler(int signo) {
    printf("Loop var set\n");
    loop = 1;
}

int main(int argc, char *argv[]) {
    struct sigaction action;
    int counter = 0;

    // install ctrlHandler
    action.sa_handler = ctrlHandler;
    action.sa_flags = 0;
    if ((sigemptyset(&action.sa_mask) == -1) || (sigaction(SIGINT, &action, NULL) == -1)) {
            perror("ERROR: Failure to set signal handler for Ctrl + C\n");
    }
    sigset_t set;
    if((sigemptyset(&set) == -1) || (sigaddset(&set, SIGINT) == -1)) {
        perror("ERROR: Failure setting SIGINT\n");
    }
    // block sigint
    if(sigprocmask(SIGINT, &set, NULL) == -1) { // block SIGTSTP
        perror("ERROR: Failure to block signal\n");
        return -1;
    }

    while(!loop) {
        printf("Counter: %d\n", counter++);
        fflush(stdout);

        // check value of counter and unblock signint
        if (counter == 5) {
            sigprocmask(SIG_UNBLOCK, &set, NULL);
        }

        sleep(1);
    }

    printf("Graceful exit\n");
    fflush(stdout);

    return 0;
}

/*
Expected output: '//' says what happens and is not printed by the code

// SIGINT blocked
Counter: 0
Counter: 1
^CCounter: 2 // Ctrl+C
Counter: 3
Counter: 4
Loop var set // SIGINT enabled
Graceful exit

*/