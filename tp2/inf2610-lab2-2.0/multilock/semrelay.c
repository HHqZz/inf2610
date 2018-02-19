
/*
 * semrelay.c
 *
 *  Created on: 2013-08-19
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#include "semrelay.h"
#include "statistics.h"
#include "multilock.h"
#include "utils.h"

void *semrelay_worker(void * data) {
    unsigned long i, j;
    struct experiment * exp_data = data;

    // TODO: protection de la boucle interne par un semrelay
    for (i = 0; i < exp_data->outer; i++) {
            sem_wait(&(((sem_t *)exp_data->lock)[exp_data->rank]));
        
            for (j = 0; j < exp_data->inner; j++) {
                /* En mode instable, le thread au rang 0 peut être tué aléatoirement */
                if (j == 0 && exp_data->unstable && exp_data->rank == 0) {
                    if (rand() / RAND_MAX < 0.1)
                        pthread_exit(NULL);
                }
                unsigned long idx = (i * exp_data->inner) + j;
                statistics_add_sample(exp_data->data, (double) idx);
            }
        sem_post(&(((sem_t *)exp_data->lock)[(exp_data->rank+1)%exp_data->nr_thread]));
        }
    return NULL;
}

void semrelay_initialization(struct experiment * exp_data) {
    int i = exp_data->nr_thread; // fils dexecution

    exp_data->data = make_statistics();
    
    // TODO: allocation d'un tableau de sémaphores sem_t dans exp_data->lock
        sem_t * semaphore = (sem_t *)malloc( i*sizeof(sem_t));
    
    // TODO: initialisation des sémaphores
        // 1 pour patager car chaine?? i comme valeur initial du semaphore
    sem_init(&(semaphore[0]),0,1);
    for(int j = 1;j< i; j++) {
        sem_init(&(semaphore[j]), 0, 0);
    }
    exp_data->lock = semaphore;
}

void semrelay_destroy(struct experiment * exp_data) {
    int i = exp_data->nr_thread;

    // copie finale dans exp_data->stats
    statistics_copy(exp_data->stats, exp_data->data);

    // TODO: destruction du verrou
    for(int j =0; j< i; j++){
        sem_destroy( &(((sem_t *)exp_data->lock)[j]));
    }
    // TODO: liberation de la memoire du verrou
    free( exp_data->lock);
    
    
}


