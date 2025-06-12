#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Process ID: %d\n", getpid());
    sleep(60); // Sleep to allow time to inspect memory
    return 0;
}