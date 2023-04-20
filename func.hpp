#ifndef HEADER_FILE
#define HEADER_FILE
#include "func.hpp"

double rand_double(double min, double max);
void daxpy_unroll(double alpha, const std::vector<double> &x, std::vector<double> &y, int block_size);
void daxpy(double a, const std::vector<double> &x, std::vector<double> &y);
void dgemv(double alpha, const std::vector<std::vector<double> >& A, const std::vector<double>& x, double beta, std::vector<double>& y);
void dgemm(double alpha, const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &B, double beta, std::vector<std::vector<double> > &C);

#endif // HEADER_FILE
