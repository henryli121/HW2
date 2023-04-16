#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

int main() {
    int ntrial = 3;
    srand(time(NULL));

    for (int n = 2; n <= 1024; n++) {
        double **A = (double **)malloc(n * sizeof(double *));
        double *x = (double *)malloc(n * sizeof(double));
        double *y = (double *)malloc(n * sizeof(double));
        double alpha = rand_double(1.0, 10.0);
        double beta = rand_double(1.0, 10.0);

        for (int i = 0; i < n; i++) {
            A[i] = (double *)malloc(n * sizeof(double));
            for (int j = 0; j < n; j++) {
                A[i][j] = rand_double(1.0, 10.0);
            }
            x[i] = rand_double(1.0, 10.0);
            y[i] = rand_double(1.0, 10.0);
        }

        struct timespec start, stop;
        double duration;

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int trial = 0; trial < ntrial; trial++) {
            dgemv(alpha, (const double **)A, x, beta, y, n);
        }
        clock_gettime(CLOCK_MONOTONIC, &stop);

        duration = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
        double avg_time = duration / ntrial;
        double FLOPs = (2 * n * n + 3 * n) / avg_time;

        printf("n = %d, avg_time = %lf ms, FLOPs = %lf\n", n, avg_time, FLOPs);
        for (int i = 0; i < n; i++) {
            free(A[i]);
        }
        free(A);
        free(x);
        free(y);
    }
    return 0;
}

