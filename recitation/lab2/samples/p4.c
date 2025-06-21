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

#define BLKSIZE 10

void fileDescriptorCheck(char *filename){
    int fd = open(filename, READ);

    printf("filedes before fork - %d\n", fd);

    pid_t pid = fork();
    if(pid == 0){
        printf("filedes of child [%d] - [%d]\n", getpid(), fd);
        close(fd);
        exit(0);
    } else {
        printf("filedes of parent [%d] - [%d]\n", getpid(), fd);
    }
    close(fd);
}

void tokenWrite(char *filename) {
    int fd = open(filename, WRITE, PERM);

    for(int i = 0; i < 3; i++){
        char fileline[1024] = {};
        sprintf(fileline, "Line for process %d\n", i + 1);
        write(fd, fileline, strlen(fileline));
    }

    close(fd);
}

void tokenRead(char *filename){
    int fd = open(filename, READ);

    pid_t parent_id = getpid();
    pid_t pid = -1;
    for(int i = 0; i < 3; i++){
        pid_t pid = fork();
        if(pid == 0) {
            char fileline[20];
            memset(fileline, 0, 20);
            read(fd, fileline, 20);
            printf("Process %d at fd position %d after reading line: %s\n", getpid(), lseek(fd, 0, SEEK_CUR), fileline);
        } else {
            break;
        }
    }
    while(wait(NULL) > 0);

    // current position in file
    int position = lseek(fd, 0, SEEK_CUR);

    printf("File descriptor position for process [%d]: [%d]\n", getpid(), position);
    close(fd);
}

int main(int argc, char *argv[]){
    char *filename = "p4_test.txt";
    tokenWrite(filename);
    tokenRead(filename);
    return 0;
}