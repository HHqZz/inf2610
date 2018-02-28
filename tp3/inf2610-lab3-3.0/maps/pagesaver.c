/*
 * libpagesaver.c
 *
 *  Created on: 2018-02-15
 *      Author: Loïc Gelle, based on a work by Francis Giraldeau
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
#include <fcntl.h>

#include "pagesaver.h"

#define BUFLEN 128

void save_maps(int suffix) {
    int ret;
    char filename[100];
    char buf[BUFLEN];
    sprintf(buf, "/proc/%d/maps", getpid());
    if (suffix > 0)
        sprintf(filename, "maps.snapshot.%d", suffix);
    else
        sprintf(filename, "maps.snapshot");
    int maps_fd = open(buf, O_RDONLY);
    int dest_fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    while((ret = read(maps_fd, buf, BUFLEN)) > 0) {
        ret = write(dest_fd, buf, ret);
        if (ret < 0)
            break;
    }
    close(maps_fd);
    close(dest_fd);
}