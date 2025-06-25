#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define WRITE (O_WRONLY|O_CREAT)
#define PERM (S_IRUSR|S_IWUSR)

int main(int argc, char *argv[]) {
    // Redirecting writes from one file to another
    int fd1 = open("file1.txt", WRITE, PERM);
    char message[100];
    memset(message, 0, sizeof(message));
    sprintf(message, "Write to file1.txt using fd %d\n", fd1);
    write(fd1, message, strlen(message));

    int fd2 = open("file2.txt", WRITE, PERM);
    memset(message, 0, sizeof(message));
    sprintf(message, "Write to file2.txt using fd %d\n", fd2);
    write(fd2, message, strlen(message));

    // Redirecting fd2 to fd1
    int ret = dup2(fd1, fd2); // fd2 is closed and now points to fd1's system file table entry

    memset(message, 0, sizeof(message));
    sprintf(message, "Write to file1.txt using fd %d\n", fd1);
    write(fd1, message, strlen(message));
    memset(message, 0, sizeof(message));
    sprintf(message, "Write to file1.txt using fd %d\n", fd2);
    write(fd2, message, strlen(message));

    close(fd2);
    close(fd1);
    
    return 0;
}