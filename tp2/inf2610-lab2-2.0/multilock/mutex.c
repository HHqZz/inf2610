/*
 * mutex.c
 *
 *  Created on: 2013-08-19
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "statistics.h"
#include "multilock.h"

#include "utils.h"

void * mutex_worker(void * data) {
    unsigned long i, j, inner;
    struct experiment * exp_data = data;

// On laisse les deux lock pour montrer la difference
    for (i = 0; i < exp_data->outer; i++) {
		if(exp_data->unstable)
			pthread_mutex_trylock(exp_data->lock); //verrouille le mutex /* modif pour robust */
		else
			pthread_mutex_lock(exp_data->lock); //verrouille le mutex 

        for (j = 0; j < exp_data->inner; j++) {
            /* En mode instable, le thread au rang 0 peut être tué aléatoirement */
            if (j == 0 && exp_data->unstable && exp_data->rank == 0) {
                if (rand() / RAND_MAX < 0.1)
                    pthread_exit(NULL);
            }
            unsigned long idx = (i * exp_data->inner) + j;
            statistics_add_sample(exp_data->data, (double) idx);
        }	
        pthread_mutex_unlock(exp_data->lock); // deverouille le mutex

    }
    return NULL;
}

void mutex_initialization(struct experiment * exp_data) {
    exp_data->data = make_statistics();


    // Allocation d'un pthread_mutex_t dans exp_data->lock
        pthread_mutex_t * mutex = malloc(sizeof(pthread_mutex_t));
        
    // Assignation du mutex 
        exp_data->lock = mutex;
        
        /* Contre le mode unstable */
	// Init attribut recursif
		pthread_mutexattr_t *attribut = malloc(sizeof(pthread_mutex_t));
		pthread_mutexattr_init(attribut);
		pthread_mutexattr_settype(attribut, PTHREAD_MUTEX_RECURSIVE_NP);
		
	// Init mutex
		pthread_mutex_init(exp_data->lock,NULL);

}

void mutex_destroy(struct experiment * exp_data) {
    statistics_copy(exp_data->stats, exp_data->data);
    free(exp_data->data);

    // TODO: destruction du verrou
    pthread_mutex_destroy(exp_data->lock);
    
    // TODO: liberation de la memoire du verrou   
    free(exp_data->lock);   
}
