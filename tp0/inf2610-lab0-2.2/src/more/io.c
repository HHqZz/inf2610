/*
 * io.c
 *
 *  Created on: 2016-01-08
 *      Authors: Hanifa Boucheneb, Thomas Bertauld
 */

#include <unistd.h>  // pour open, write et read
#include <fcntl.h>
#include <stdint.h>

#define taille 80

#define __stdin 0
#define __stdout 1
#define __stderr 2

int main(void)
{ 
	int8_t fd, nbcar;
	char buf[taille];
	
	fd = open("fich", O_CREAT | O_RDWR); // créer un fichier
	
	if(fd == -1) { 
		write(__stderr, "Erreur d’ouverture \n", 25);
		return -1;
	}
	write(__stdout, "Ouverture avec succès \n" , 30);
	
	// copier les données à partir du clavier dans le fichier
	while ((nbcar = read(__stdin, buf, taille)) > 0) {
		if( write(fd, buf, nbcar) == -1) {
			return -1;
		}
	}
	
	return 0;
}