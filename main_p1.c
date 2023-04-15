#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void daxpy(double a, const double *x, double *y, int n);
double rand_double(double min, double max);

int main () {
    //initialization
    int ntrial = 1000;
    srand(time(NULL));
    /*FILE *output_file = fopen("output.txt", "w");*/

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

        //initializa the time and measure n trival times:
        struct timespec start, stop;
        double total_time = 0;

        for (int j = 0; j<ntrial; j++) {
            //start counting time:
            clock_gettime(CLOCK_MONOTONIC, &start);
            daxpy(alpha, x, y, n);
            clock_gettime(CLOCK_MONOTONIC, &stop);
            double duration = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
            total_time+= duration;
        }

    //find the FLOPs
     double avg_time = total_time/ntrial;
     double FLOPs = (2 * n) / avg_time; //f(n) = 2*n scaler multiplication and addition
     printf("for n = %d, average time = %lf s, FLOPs = %lf\n", n, avg_time, FLOPs);

     //fprintf(output_file, "%d, %lf\n", n, FLOPs);
    //free the memory
     free(x);
     free(y);
    }

//fclose(output_file);
return 0;
}