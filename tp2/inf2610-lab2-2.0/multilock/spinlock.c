/*
 * spinlock.c
 *
 *  Created on: 2013-08-19
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "minispinlock.h"
#include "statistics.h"
#include "multilock.h"

/* Spinlock: verrou actif
 *
 * Voir l'implémentation du verrou dans le fichier minispinlock.asm
 * et l'interface dans minispinlock.h
 */
void *spinlock_worker(void * data) {
    unsigned long i, j;
    struct experiment * exp_data = data;

    // TODO: protection de la boucle interne par un spinlock
    for (i = 0; i < exp_data->outer; i++) {
        for (j = 0; j < exp_data->inner; j++) {
            /* En mode instable, le thread au rang 0 peut être tué aléatoirement */
            if (j == 0 && exp_data->unstable && exp_data->rank == 0) {
                if (rand() / RAND_MAX < 0.1)
                    pthread_exit(NULL);
            }
            unsigned long idx = (i * exp_data->inner) + j;
            statistics_add_sample(exp_data->data, (double) idx);
        }
    }
    return NULL;
}

void spinlock_initialization(struct experiment * exp_data) {
    exp_data->data = make_statistics();

    // TODO: allocation d'un long dans exp_data->lock

    // TODO: initialisation à zéro
}

void spinlock_destroy(struct experiment * exp_data) {
    statistics_copy(exp_data->stats, exp_data->data);
    free(exp_data->data);

    // TODO: liberation de la memoire du verrou
}

