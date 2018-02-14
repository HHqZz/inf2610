/*
 * baz.c
 *
 *  Created on: 2013-08-15
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "whoami.h"

int main(int argc, char **argv) {
	increment_rank();
	whoami("baz");
	printf(argv[1]);
	
	int n = atoi(argv[1]);
	
	if(--n> 0){ 
	      char *s;
	      asprintf(&s, "%d", n);
	      execlp("foo", "foo", s, NULL);
	}
	return 0;
}
