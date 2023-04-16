#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

int main() {
//initialiaztion
    int n = 2048;
    int ntrial = 1000;
    int block_sizes[] = {1, 2, 4, 8, 16, 32, 64};
    int block_len = sizeof(block_sizes) / sizeof(block_sizes[0]);
    srand(time(NULL));
    FILE *output_file = fopen("output2.txt", "w");

//allocate memeories:
    double *x = (double*)malloc(n*sizeof(double));
    double *y = (double*)malloc(n*sizeof(double));
    //assign alpha: random number between (1, 10)
    double alpha = rand_double(1.0, 10.0);

//assign random values to x and y also between (1, 10)
    for (int i = 0; i < n; i++) {
        x[i] = rand_double(1.0, 10.0);
        y[i] = rand_double(1.0, 10.0);
    }
//go through each block size:
    for (int k = 0; k < block_len; k++) {
        int block_size = block_sizes[k];
        struct timespec start, stop;
        double duration;

        //start counting time:
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int j = 0; j<ntrial; j++) {
            daxpy_unroll(alpha, x, y, n, block_size);
        }
        clock_gettime(CLOCK_MONOTONIC, &stop);
        duration = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
        double avg_time = duration/ntrial;
        double FLOPs = (2 * n) / avg_time;

    printf("for block size = %d, average time = %lf s, FLOPs = %lf\n", block_size, avg_time, FLOPs);
    fprintf(output_file, "%d, %lf\n", block_size, FLOPs);
    }

    free(x);
    free(y);

    fclose(output_file);

    return 0;
}