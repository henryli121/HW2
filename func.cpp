#include <cstdlib>
#include<vector>
#include "func.hh"

// Function
void daxpy(double a, const std::vector<double> &x, std::vector<double> &y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] += a * x[i];
    }
}

// Random number generator
double rand_double(double min, double max) {
    double random_double = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
    return min + random_double * (max - min);
}

// Depth 4 loop unroll function:
void daxpy_unroll(double alpha, const std::vector<double> &x, std::vector<double> &y, int n, int block_size) {
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

// Function for p3
void dgemv(double alpha, const std::vector<std::vector<double> >& A, const std::vector<double>& x, double beta, std::vector<double>& y, int n) {
    for (int i = 0; i < n; i++) {
        double temp = 0.0;
        for (int j = 0; j < n; j++) {
            temp += A[i][j] * x[j];
        }
        y[i] = alpha * temp + beta * y[i];
    }
}
