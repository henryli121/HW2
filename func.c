#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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