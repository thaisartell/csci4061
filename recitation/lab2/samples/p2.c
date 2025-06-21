#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {

    // echo command prints the input passed to it onto the terminal
    // $ echo Hello 4061
    // Hello 4061

    if (argc < 2) {
        printf("Usage: ./p2.o <mode>\n");
        /*
            mode values
                0: execl
                1: execlp
                2: execv
                3: execvp
        */
       exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    /*
        Note that the second argument (or first index of second argument for v variant) in all 
        the exec functions is always the program name in both p and v variants.
        This could be a dummy string as well.
    */
    if(pid == 0) {
        int mode = atoi(argv[1]);
        if(mode == 0){ // execl
            printf("execl\n");
            int ret = execl("/bin/echo", "echo", "Hello", "4061", NULL); // specify path
            if (ret == -1){
                printf("ERROR: execl failed\n");
                exit(EXIT_FAILURE);
            }
        } else if(mode == 1) { // execlp
            printf("execlp\n");
            int ret = execlp("echo", "echo", "Hello", "4061", NULL); // no need to specify path if command location in PATH
            if (ret == -1){
                printf("ERROR: execlp failed\n");
                exit(EXIT_FAILURE);
            }
        } else if(mode == 2) { //execv
            printf("execv\n");
            char *args[] = {"/bin/echo", "Hello", "4061", NULL};
            int ret = execv(args[0], args);
            if (ret == -1){
                printf("ERROR: execv failed\n");
                exit(EXIT_FAILURE);
            }
        } else if(mode == 3) { //execvp
            printf("execvp\n");
            char *args[] = {"echo", "Hello", "4061", NULL};
            int ret = execvp(args[0], args);
            if (ret == -1){
                printf("ERROR: execvp failed\n");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        wait(NULL);
    }

    /*
        You may use any of the above for your PA1
    */
    
    return 0;
}