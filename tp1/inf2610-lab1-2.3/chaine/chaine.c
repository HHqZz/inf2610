/*
 * chaine.c
 *
 *  Created on: 2013-08-15
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include "whoami.h"

/* Astuce:
 * Conversion de string à nombre: atoi()
 * Conversion de nombre à string: asprintf()
 */

int main(int argc, char **argv) {
	int nombreAppels = 2;
	if (argc == 2) {
	    nombreAppels = atoi(argv[1]);
	}

	// ajoute le répertoire courant dans $PATH
	add_pwd_to_path(argv[0]);

	increment_rank();
	whoami("chaine");

	// Exécution de n cycles foo bar baz
	char *s;
	asprintf(&s, "%d", nombreAppels);
	if(nombreAppels>0){
	     execlp("foo", "foo", s, NULL);
	}
	
	return 0;
}
