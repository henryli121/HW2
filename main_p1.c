#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

int main () {
    //initialization
    int ntrial = 1000;
    srand(time(NULL));
    FILE *output_file = fopen("output.txt", "w");

    //loop from 2 to 1024 with increment 1
    for (int n = 2; n <= 1024; n += 1) {
        //allocate memeories for the pointer:
        double *x = (double*)malloc(n*sizeof(double));
        double *y = (double*)malloc(n*sizeof(double));
        //assign alpha: random number between (1, 10)
        double alpha = rand_double(1.0, 10.0);
       
        //assign random values to x and y also between (1, 10)
        for (int i = 0; i < n; i++) {
            x[i] = rand_double(1.0, 10.0);
            y[i] = rand_double(1.0, 10.0);
        }

        //initializa the time
        struct timespec start, stop;
         //start counting time:
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int j = 0; j<ntrial; j++) {
            daxpy(alpha, x, y, n);
        }
        clock_gettime(CLOCK_MONOTONIC, &stop);

        //find the FLOPs
        double duration = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
        double avg_time = duration/ntrial;
        double FLOPs = (2 * n) / avg_time; //f(n) = 2*n scaler multiplication and addition
        printf("for n = %d, average time = %lf s, FLOPs = %lf\n", n, avg_time, FLOPs);

        fprintf(output_file, "%d, %lf\n", n, FLOPs);
        //free the memory
        free(x);
        free(y);
    }

fclose(output_file);
return 0;
}