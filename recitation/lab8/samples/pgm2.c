#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/*
    Blocking and unblocking Ctrl+Z

    The code blocks Ctrl + Z for 5 seconds

    After executing the code, immediately do Ctrl+Z
*/
int main(int argc, char *argv[]) {
    sigset_t set;

    if((sigemptyset(&set) == -1) || // check if set is empty
        (sigaddset(&set, SIGTSTP) == -1)) // add SIGTSTP to set
            perror("ERROR: Failure setting SIGTSTP\n");
    
    if(sigprocmask(SIG_BLOCK, &set, NULL) == -1) { // block SIGTSTP
        perror("ERROR: Failure to block signal\n");
        return -1;
    }

    int counter = 0;
    while(1) {
        printf("Counter: %d\n", counter++);
        fflush(stdout);

        if(counter == 5) {
            if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1) { // unblock SIGTSTP
                perror("ERROR: Failure to unblock signal\n");
                return -1;
            }       
        }
        sleep(2);
    }
    return 0;
}