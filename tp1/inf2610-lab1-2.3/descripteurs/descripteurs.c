#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("printf 1 du processus parent %d \n", getpid());
    printf ("printf 2 du processus parent %d ", getpid());
    write(1, "write 1 ", 8);
    if (!fork()) {
        write(1, "write 2 du processus fils ", 26);
        printf("printf 3 du processus fils %d \n", getpid());
    } else {
        write(1, "write 2 du processus parent ", 28);
        printf("printf 3 du processus parent %d \n", getpid());
    }
    return 0;
}

