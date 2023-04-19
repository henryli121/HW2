#ifndef HEADER_FILE
#define HEADER_FILE
#include "refBLAS.hpp"

double rand_double(double min, double max);
void daxpy_unroll(double alpha, const std::vector<double> &x, std::vector<double> &y, int block_size);

template <typename T>
void daxpy(T a, const std::vector<T> &x, std::vector<T> &y);
template <typename T>
void dgemv(T alpha, const std::vector<std::vector<T> >& A, const std::vector<T>& x, T beta, std::vector<T>& y);
template <typename T>
void dgemm(T alpha, const std::vector<std::vector<T> > &A, const std::vector<std::vector<T> > &B, T beta, std::vector<std::vector<T> > &C);

extern template void daxpy<double>(double a, const std::vector<double> &x, std::vector<double> &y);
extern template void dgemv<double>(double alpha, const std::vector<std::vector<double> >& A, const std::vector<double>& x, double beta, std::vector<double>& y);
extern template void dgemm<double>(double alpha, const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &B, double beta, std::vector<std::vector<double> > &C);
/*
// Function
template <typename T>
void daxpy(T a, const std::vector<T> &x, std::vector<T> &y, int n) {
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
template <typename T>
void dgemv(T alpha, const std::vector<std::vector<T> >& A, const std::vector<T>& x, T beta, std::vector<T>& y, int n) {
    for (int i = 0; i < n; i++) {
        double temp = 0.0;
        for (int j = 0; j < n; j++) {
            temp += A[i][j] * x[j];
        }
        y[i] = alpha * temp + beta * y[i];
    }
}


// Function for p4:
template <typename T>
void dgemm(T alpha, const std::vector<std::vector<T> > &A, const std::vector<std::vector<T> > &B, T beta, std::vector<std::vector<T> > &C, int n) {
    std::vector<std::vector<double> > dot_prod(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double temp = 0.0;
            for (int k = 0; k < n; k++) {
                temp += A[i][k] * B[k][j];
            }
            dot_prod[i][j] = alpha * temp;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = dot_prod[i][j] + beta * C[i][j];
        }
    }
}
*/

#endif // HEADER_FILE
