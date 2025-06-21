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
    if(argc < 2){
        printf("Usage: ./chain.o <number of child processes>");
        exit(EXIT_FAILURE);
    }
    /*
        main -> 1 -> 2 -> 3 -> 4 -> 5
        main creates 1 creates 2 creates 3 creates 4 creates 5
        Each process will wait for its child to complete

        Expected output: pids.txt
        Main process 17642
        Process 17643
        Process 17644
        Process 17645
        Process 17646
        Process 17647
    */

    // Follow samples/p3.c. The code is almost the same. You need to open a file,
    // share it across processes and write the process ids
    // parents should wait for child processes to complete
    int n = atoi(argv[1]);

    // File IO
    int fd = open("pids.txt", WRITE, PERM);
    if (fd == -1) {
        exit(EXIT_FAILURE);
    }

    char first[1024] = {};
    sprintf(first, "Main Process: %d\n", getpid());

    int i;
    for(i = 0; i < n; i++) {
        if (i == 0) {
            write(fd, first, strlen(first));
        }
        int pid = fork();
        char pid_word[32] = {};
        sprintf(pid_word, "Process: %d\n", getpid());
        if(pid == 0){
            write(fd, pid_word, strlen(pid_word));
            continue;
        } else {
            break;
        }
    }

    if(i != n){ // wait will return -1 for the last process as there is no one to wait for
        int pid = wait(NULL); // wait for child
        if(pid == -1){
            printf("ERROR: Process %d failed waiting\n", getpid());
            exit(EXIT_FAILURE);
        } else {
            printf("Process %d completed wait for child %d\n", getpid(), pid);
        }
    }
    close(fd);
    return 0;
}