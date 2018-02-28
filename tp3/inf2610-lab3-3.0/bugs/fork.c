/*
 * fork.c
 *
 *  Created on: 2018-02-16
 *      Author: Loïc Gelle
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static char message[30];

int main(int argc, char **argv) {
    
    if (fork()) {
        sprintf(message, "Greeting from parent");
        printf("Parent printing message from address %p: %s\n", &message, message);
        wait(NULL);
    } else {
        sprintf(message, "Hello from child");
        printf("Child printing message from address %p: %s\n", &message, message);
    }

    return 0;
}
