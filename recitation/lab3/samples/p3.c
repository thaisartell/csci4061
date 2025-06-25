#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define WRITE (O_WRONLY|O_CREAT)
#define PERM (S_IRUSR|S_IWUSR)

int main(int argc, char *argv[]) {
    // Duplicating stdout
    int new_stdout_fd = dup(STDOUT_FILENO);

    printf("Writing to stdout using printf\n");
    char *message = "Writing to stdout using write and new_stdout_fd\n";
    write(new_stdout_fd, message, strlen(message));
    close(new_stdout_fd);
    return 0;
}