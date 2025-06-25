#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define WRITE (O_WRONLY|O_CREAT)
#define PERM (S_IRUSR|S_IWUSR)

int main(int argc, char *argv[]) {

    if(argc != 2) {
        perror("Usage: ./child.o <read end of pipe>");
        exit(EXIT_FAILURE);
    }

    int read_fd = atoi(argv[1]);
    char message[100];
    memset(message, 0, 100);
    read(read_fd, message, 100);

    printf("Message from server: %s\n", message);
    // You need to close the pipe properly
    return 0;
}