#include "func.h"
#include <stdio.h>
#include <stdlib.h>


//function
void daxpy(double a, const double *x, double *y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] += a * x[i];
    }
}

//random number generator
double rand_double(double min, double max) {
    double random_double = (double)rand() / (double)RAND_MAX;
    return min + random_double * (max - min);
}

//depth 4 loop unroll function:
void daxpy_unroll(double alpha, const double *x, double *y, int n, int block_size) {
    for (int i = 0; i < n; i += block_size * 4) {
        for (int j = 0; j < block_size; j++) {
            y[i + j] += alpha * x[i + j];
            y[i + j + block_size] += alpha * x[i + j + block_size];
            y[i + j + 2 * block_size] += alpha * x[i + j + 2 * block_size];
            y[i + j + 3 * block_size] += alpha * x[i + j + 3 * block_size];
        }
    }

    for (int i = (n / (block_size * 4)) * block_size * 4; i < n; i++) {
        y[i] += alpha * x[i];
    }
}
