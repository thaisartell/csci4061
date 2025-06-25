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
    
    char message[100];
    memset(message, 0, sizeof(message));
    sprintf(message, "tmp.txt inode: %ld\n", ?);
    

    // Step 2: Duplicate stdout

    // Step 3: Redirect stdout to fd and use printf to write the file descriptors of tmp.txt and the duplicated stdout to tmp.txt
    // Important: After printf, call fflush(stdout) otherwise the internal buffer of printf will not flush to the file
    
    printf("tmp.txt fd - %d : dup stdout - %d\n", ?, ?);
    fflush(stdout);


    // Step 4: Restore stdout using the duplicated stdout
    
    // Step 5: Close all file descriptors
    
    printf("STDOUT_FILENO restored.\n");
    
    return 0;
}