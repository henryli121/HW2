#include <cstdlib>
#include<vector>
#include<iostream>
#include "func.hpp"

// Random number generator
double rand_double(double min, double max) {
    double random_double = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
    return min + random_double * (max - min);
}

// Depth 4 loop unroll function:
void daxpy_unroll(double alpha, const std::vector<double> &x, std::vector<double> &y, int block_size) {
    int n = x.size();
    if (n!=y.size()) {
        throw std::invalid_argument("Vectors x and y must have the same shape.");
    }
    if (block_size > n) {
        throw std::invalid_argument("Block size must be less than or equal to the vector size n.");
    }

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

// Function
void daxpy(double a, const std::vector<double> &x, std::vector<double> &y) {
    int n = x.size();
    if (n!=y.size()) {
        throw std::invalid_argument("Vectors x and y must have the same shape.");
    }

    for (int i = 0; i < n; i++) {
        y[i] += a * x[i];
    }
}

// Function for p3
void dgemv(double alpha, const std::vector<std::vector<double> >& A, const std::vector<double>& x, double beta, std::vector<double>& y) {
    int m = A.size();
    int n = A[0].size();
    int x_size = x.size();
    int y_size = y.size();
    if (n != x_size || m != y_size) {
        throw std::invalid_argument("Input dimensions are not compatible.");
    }


    for (int i = 0; i < m; i++) {
        double temp = 0.0;
        for (int j = 0; j < n; j++) {
            temp += A[i][j] * x[j];
        }
        y[i] = alpha * temp + beta * y[i];
    }
}


// Function for p4:
void dgemm(double alpha, const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &B, double beta, std::vector<std::vector<double> > &C) {
    int m = A.size();
    int p = A[0].size();
    int n = B[0].size();
    if (p != B.size() || m != C.size() || n != C[0].size()) {
        throw std::invalid_argument("Input dimensions are not compatible.");
    }

    std::vector<std::vector<double> > dot_prod(m, std::vector<double>(n, 0.0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double temp = 0.0;
            for (int k = 0; k < p; k++) {
                temp += A[i][k] * B[k][j];
            }
            dot_prod[i][j] = alpha * temp;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = dot_prod[i][j] + beta * C[i][j];
        }
    }
}

