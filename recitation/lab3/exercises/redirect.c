#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define WRITE (O_WRONLY|O_CREAT)
#define PERM (S_IRUSR|S_IWUSR)

/*
    Expected output: Numerical values may change

        tmp.txt
            tmp.txt inode: 11142215
            tmp.txt fd - 3 : dup stdout - 4

        terminal:
            STDOUT_FILENO restored.

*/

int main(int argc, char *argv[]) {
    // Step 1: Open a new file tmp.txt and write the inode number of tmp.txt to tmp.txt
    
    int fd1 = open("tmp.txt", WRITE, PERM);

    char *pathname = "./tmp.txt";
    struct stat statbuf;
    int ret = stat(pathname, &statbuf);

    char message[100];
    memset(message, 0, sizeof(message));
    sprintf(message, "tmp.txt inode: %ld\n", statbuf.st_ino);

    write(fd1, message, strlen(message));

    // Step 2: Duplicate stdout

    int new_stdout_fd = dup(STDOUT_FILENO); 

    // Step 3: Redirect stdout to fd and use printf to write the file descriptors of tmp.txt and the duplicated stdout to tmp.txt
    // Important: After printf, call fflush(stdout) otherwise the internal buffer of printf will not flush to the file

    int ret2 = dup2(fd1, STDOUT_FILENO);
    
    printf("tmp.txt fd - %d : dup stdout - %d\n", fd1, new_stdout_fd);
    fflush(stdout);

    // Step 4: Restore stdout using the duplicated stdout
    
    int restore = dup2(new_stdout_fd, STDOUT_FILENO);

    // Step 5: Close all file descriptors
    
    printf("STDOUT_FILENO restored.\n");
    close(fd1);
    
    return 0;
}