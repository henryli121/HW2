#ifndef HEADER_FILE
#define HEADER_FILE
void daxpy_unroll(double alpha, const double *x, double *y, int n, int block_size);
void daxpy(double a, const double *x, double *y, int n);
double rand_double(double min, double max);

#endif