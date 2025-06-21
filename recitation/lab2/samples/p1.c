#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]) {

    // getpid(): get current process id
    // getppid(): get the parent id of current process
    
    printf("Parent id: %d\n", getpid());

    pid_t child = fork();
    printf("My id: %d and child: %d\n", getpid(), child);

    if(child == 0){
        printf("This is the explicit child execution region\n");
        printf("Child %d is spawned by Parent %d\n", getpid(), getppid());
    } else {
        printf("This is the explicit parent execution region\n");
    }
    
    // Run the program multiple times and observe what happens 
    // to the value of getppid()
    return 0;
}