#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#define PATHLEN 1024

/*
    The code is almost same as samples/p6.c. You need to traverse recursively through directory structures.
    It will be one or two lines of code change wrt p6.c

    Expected Output:
    File: nestdir/t2.txt
    File: nestdir/t1.txt
    Directory: nestdir/d1
    File: nestdir/d1/t3.txt
    Directory: nestdir/d1/d2
    File: nestdir/d1/d2/t4.txt
*/

int directoryTraversal(char *directory) {
    struct dirent *entry;
    DIR *dir = opendir(directory);

    // bad input
    if(dir == NULL) {
        printf("ERROR: %s directory does not exist.\n", directory);
        return -1;
    }
    
    while((entry = readdir(dir)) != NULL) {
        char path[PATHLEN] = {};

        // if directory is itself or parent
        if ((strcmp(entry->d_name, ".") == 0) ||
        (strcmp(entry->d_name, "..") == 0)) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
        if (entry->d_type == DT_REG) { // regular file
            printf("File: %s\n", path);
        }
        else if (entry->d_type == DT_DIR) { // further path
            printf("Directory: %s\n", path);
            directoryTraversal(path);
        }
    }
    closedir(dir);
    
    return 0;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: ./traverse.o <directory>\n");
        exit(EXIT_FAILURE);
    }

    char *directory = argv[1];
    directoryTraversal(directory);

    return 0;
}
