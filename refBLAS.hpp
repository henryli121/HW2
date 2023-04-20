#ifndef HEADER_FILE
#define HEADER_FILE
#include "refBLAS.hpp"

double rand_double(double min, double max);
void daxpy_unroll(double alpha, const std::vector<double> &x, std::vector<double> &y, int block_size);

template <typename T>
void axpy(T a, const std::vector<T> &x, std::vector<T> &y);
template <typename T>
void gemv(T alpha, const std::vector<std::vector<T> >& A, const std::vector<T>& x, T beta, std::vector<T>& y);
template <typename T>
void gemm(T alpha, const std::vector<std::vector<T> > &A, const std::vector<std::vector<T> > &B, T beta, std::vector<std::vector<T> > &C);

extern template void axpy<double>(double a, const std::vector<double> &x, std::vector<double> &y);
extern template void gemv<double>(double alpha, const std::vector<std::vector<double> >& A, const std::vector<double>& x, double beta, std::vector<double>& y);
extern template void gemm<double>(double alpha, const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &B, double beta, std::vector<std::vector<double> > &C);
#endif // HEADER_FILE
