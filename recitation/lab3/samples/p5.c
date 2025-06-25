#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1){
        perror("Pipe creation failed\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if(pid == 0) {
        close(fd[1]); // close write end of pipe in child
        char message[100];
        read(fd[0], message, 100);
        printf("Child read parent message: %s\n", message);
        close(fd[0]);
        exit(EXIT_SUCCESS);
    } else {
        close(fd[0]); // close read end of pipe in parent
        char *message = "CSCI 4061";
        printf("Parent sending message: %s\n", message);
        write(fd[1], message, strlen(message));
        close(fd[1]);
    }

    return 0;
}