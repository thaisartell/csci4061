#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#define PATHLEN 1024

int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Usage: ./p6.o <directory>");
        exit(EXIT_FAILURE);
    }

    char *directory = argv[1];
    
    struct dirent *entry;
    DIR *dir = opendir(directory);

    if(dir == NULL) {
        printf("ERROR: %s directory does not exist.\n", directory);
        return -1;
    }

    while((entry = readdir(dir)) != NULL) {
        if((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
            continue; // skip . and .. present in directories

        char path[PATHLEN];
        memset(path, 0, PATHLEN);
        if(entry->d_type == DT_DIR) {
            sprintf(path, "%s/%s", directory, entry->d_name);
            printf("Directory: %s\n", path);
        } else {
            sprintf(path, "%s/%s\n", directory, entry->d_name);
            printf("File: %s\n", path);
        }
    }
    closedir(dir);
    
    return 0;
}