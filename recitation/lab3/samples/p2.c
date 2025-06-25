#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    char *pathname = "./p1.c";
    struct stat statbuf;
    int ret = stat(pathname, &statbuf);
    if(ret == -1) {
        printf("ERROR: Failure accessing stat info.\n");
        exit(EXIT_FAILURE);
    }

    printf("File %s inode: %ld\n", pathname, statbuf.st_ino);
    return 0;
}