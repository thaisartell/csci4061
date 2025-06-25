#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

/*
    Expected output:
    Server sending message: CSCI 4061
    Message from server: CSCI 4061 
*/
int main(int argc, char *argv[]) {
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1){
        perror("Pipe creation failed\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if(pid == 0) {
        // close pipe ends properly
        // use exec* to execute ./child.o with read fd as the argument
        ???
    } else {
        // close pipe ends properly
        char *message = "CSCI 4061";
        printf("Server sending message: %s\n", message);
        write(?, message, strlen(message));
        // close pipe ends properly
    }

    return 0;
}