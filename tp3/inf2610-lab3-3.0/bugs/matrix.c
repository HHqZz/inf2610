/*
 * matrix.c
 *
 *  Created on: 2018-02-16
 *      Author: Loïc Gelle
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 16384
static int matrix[SIZE][SIZE] = {{0}};

void matrix_multiply_jki() {
    int a[SIZE][SIZE] = {{0}};
    int b[SIZE][SIZE] = {{0}};
    int c[SIZE][SIZE] = {{0}};
    int r;
    for (int j = 0; j < SIZE; j++) {
        for (int k = 0; k < SIZE; k++) {
            r = b[k][j];
            for (int i = 0; i < SIZE; i++)
                c[i][j] += a[i][k] * r;
        }
    }
}

void matrix_multiply_kij() {
    int a[SIZE][SIZE] = {{0}};
    int b[SIZE][SIZE] = {{0}};
    int c[SIZE][SIZE] = {{0}};
    int r;
    for (int k = 0; k < SIZE; k++) {
        for (int i = 0; i < SIZE; i++) {
            r = a[i][k];
            for (int j = 0; j < SIZE; j++)
                c[i][j] += r * b[k][j];
        }
    }
}

void matrix_multiply_ijk() {
    int a[SIZE][SIZE] = {{0}};
    int b[SIZE][SIZE] = {{0}};
    int c[SIZE][SIZE] = {{0}};
    int sum;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum = 0;
            for (int k = 0; k < SIZE; k++)
                sum += a[i][k] * b[k][j];
            c[i][j] = sum;
        }
    }
}

void matrix_sum_b() {
    long sum = 0;
    for (int j = 0; j < SIZE; j++)
        for (int i = 0; i < SIZE; i++)
            sum += matrix[i][j];
}

void matrix_sum_a() {
    long sum = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            sum += matrix[i][j];
}

int main(int argc, char **argv) {
    
    if (argc < 2) {
        printf("Please specify the function to use: a or b\n");
        return -1;
    }
    if (strcmp(argv[1], "a") == 0)
        matrix_sum_a();
    else if (strcmp(argv[1], "b") == 0)
        matrix_sum_b();
    else {
        printf("error: function must be a or b\n");
        return -1;
    }

    return 0;
}
