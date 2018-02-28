/*
 * segfault.c
 *
 *  Created on: 2013-10-22
 *      Author: francis
 *  Modified on: 2018-02-15
 *      Author: Loïc Gelle
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
#include <string.h>

#include "pagesaver.h"

static volatile char *addr;
static volatile int offset;

/*
 * La fonction segfault_handler intercepte le signal SIGSEGV. De cette manière,
 */
void segfault_handler(int signal) {
    printf("\nWe have a problem:\n");
    printf("segfault at addr=%p offset=0x%x (%f kio)\n", addr, offset, offset / 1024.0);
    exit(1);
}

void memory_scan(void *data, int direction) {
    int i; (void) i;
    volatile char bidon = 0; (void) bidon;
    char *start = (char *) data; (void) start;

    printf("direction=%d\n", direction);

    /* TODO: Lire, octet par octet, jusqu'à la réception du signal SIGSEGV.
     *
     * Dans une boucle:
     * 1 - mettre à jour la variable offset
     * 2 - calculer l'adresse à accéder dans addr
     * 3 - appel à __sync_synchronize(); (empêche le compilateur de réordonner les instructions)
     * 4 - lire la valeur à l'adresse addr dans la variable bidon (force l'accès à cette adresse)
     *
     * Lecture seulement de la mémoire. Si le balayage écrase de la mémoire
     * utile au programme, alors il se peut que son comportement soit modifié.
     */

    printf("No segfault!\n");
    return;
}

int main(int argc, char **argv) {
    int dir = 0; (void) dir;
    long *myptr = malloc(sizeof(long)); (void)myptr;
    long *ref;

    for (int i=0; i < 23000; i++){ 
        ref = malloc(sizeof(long));
        *ref = 0;
    }

    if (argc < 2) {
        printf("Please specify the direction: u (up) ou d (down)\n");
        return -1;
    }
    if (strcmp(argv[1], "u") == 0)
        dir = 1;
    else if (strcmp(argv[1], "d") == 0)
        dir = -1;
    else {
        printf("error: direction must be u (up) or d (down)\n");
        return -1;
    }

    // TODO: enregister fonction segfault_handler au signal SIGSEGV

    save_maps(-1);

    // TODO: appel à memory_scan()

    printf("done\n");
    return 0;
}
