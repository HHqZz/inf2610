/*
 * malloc.c
 *
 *  Created on: 2013-10-22
 *      Author: francis
 *  Modified on: 2018-02-15
 *      Author: Loïc Gelle
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "pagesaver.h"

void* foo(void* p) {
    // Save maps state after thread creation
    save_maps(2);

    return NULL;
}

int main(int argc, char **argv) {
    pthread_t thread;

    // Save initial maps state
    save_maps(1);

    if (pthread_create(&thread, NULL, foo, NULL)) {
        printf("Thread creation error\n");
        return -1;
    }
    if (pthread_join(thread, NULL))
    {
        printf("Thread join error\n");
        return -1;
    }

    printf("done\n");
    return 0;
}
