#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

#define READ O_RDONLY
#define WRITE (O_WRONLY|O_CREAT)
#define PERM (S_IRUSR|S_IWUSR)

int main(int argc, char *argv[]) {

    int fd = open("p1_test.txt", WRITE, PERM);
    char message[100];
    memset(message, 0, sizeof(message));
    sprintf(message, "main process %d\n", getpid());
    
    int ret = write(fd, message, strlen(message));
    if(ret == -1){
        printf("ERROR: Failure to write.\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if(pid == 0){
        off_t offset = lseek(fd, 0, SEEK_CUR);
        if (offset == -1) {
            printf("ERROR: Fd access failed.\n");
            exit(EXIT_FAILURE);
        }
        printf("Child FD location: %ld\n", offset);
        
        memset(message, 0, sizeof(message));

        sprintf(message, "child process %d\n", getpid());
        ret = write(fd, message, strlen(message));
        if(ret == -1){
            printf("ERROR: Failure to write.\n");
            exit(EXIT_FAILURE);
        }   
    } else {
        off_t offset = lseek(fd, 0, SEEK_CUR);
        if (offset == -1) {
            printf("ERROR: Fd access failed.\n");
            exit(EXIT_FAILURE);
        }
        printf("Parent FD location: %ld\n", offset);
        
        memset(message, 0, sizeof(message));

        sprintf(message, "parent process %d\n", getpid());
        ret = write(fd, message, strlen(message));
        if(ret == -1){
            printf("ERROR: Failure to write.\n");
            exit(EXIT_FAILURE);
        }
    }

    ret = close(fd);
    if(ret == -1){
        printf("ERROR: Failure closing fd.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}