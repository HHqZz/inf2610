/*
 * write_printf.c
 *
 *  Created on: 2016-01-08
 *      Authors: Hanifa Boucheneb, Thomas Bertauld
 */

#include <unistd.h>             /* pour write */
#include <stdio.h>              /* pour printf */

#define __stdout 1

int main(void) {
	
	printf(" ici 1er printf ");
	write(__stdout," ici 1er write ", 16);
	printf(" ici 2eme printf ");
	write(__stdout," ici 2eme write ", 17);
	printf("fin de ligne de printf \n");
	write(__stdout, " ici 3eme write \n",18);
	
	return 0;
}