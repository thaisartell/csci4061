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
    int fd[2];  //fd[0] read, fd[1] write
    int ret = pipe(fd);
    if(ret == -1){
        perror("Pipe creation failed\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if(pid == 0) {  // CHILD: want CHILD to READ
        // close pipe ends properly

        close(fd[1]);

        // use exec* to execute ./child.o with read fd as the argument
        // char* read_fd = itoa(argv[1]);
        char read_fd[100];
        sprintf(read_fd, "%d", fd[0]);
        char* argv2[] = {"./child.o", read_fd, NULL};
        execv("./child.o", argv2);

    } else {    // PARENT: want PARENT to WRITE
        // close pipe ends properly

        // int num2 = dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        // close(fd[1]);

        char *message = "CSCI 4061";
        printf("Server sending message: %s\n", message);
        write(fd[1], message, strlen(message));
        // close pipe ends properly
        close(fd[1]);
    }

    return 0;
}