#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {

    pid_t pid = fork();
    if(pid == 0) { // Use execl for fanout.o with argument 5
        int ret1 = execl("./fanout.o", "fanout", argv[1], NULL);
        if (ret1 == -1) {
            exit(EXIT_FAILURE);
        }
    }
    wait(NULL);

    pid = fork();
    if(pid == 0) { // Use execv for traverse.o with argument nestdir
        char *args[] = {"./traverse.o", "nestdir",  NULL};
        int ret2 = execv(args[0], args);
        if (ret2 == -1) {
            exit(EXIT_FAILURE);
        }
    }
    wait(NULL);

    return 0;

}