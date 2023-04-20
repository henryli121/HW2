#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include "refBLAS.hpp"

int main() {
    // Initialization
    int ntrial_daxpy = 1024;
    int ntrial_dgemv = 100;
    std::srand(std::time(0));

    // Loop for daxpy
    for (int n = 2; n <= 1024; n++) {
        // Allocate memories for the pointer:
        std::vector<double> x(n);
        std::vector<double> y(n);

        // Assign alpha: random number between (0, 1)
        double alpha = rand_double(0.0, 1.0);
       
        // Assign random values to x and y also between (0, 1)
        for (int i = 0; i < n; i++) {
            x[i] = rand_double(0.0, 1.0);
            y[i] = rand_double(0.0, 1.0);
        }

        // Initialize the time
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < ntrial_daxpy; j++) {
            axpy<double>(alpha, x, y);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        // Find the FLOPs
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        double avg_time = duration / static_cast<double>(ntrial_daxpy);
        double FLOPs = (2.0 * n) / (avg_time * 1e-6); // f(n) = 2 * n scaler multiplication and addition
        std::cout << "for n = " << n << ", average time = " << avg_time * 1e-6 << " s, FLOPs = " << FLOPs << std::endl;
    }
    // Loop for dgemv
    for (int n = 2; n <= 1024; n++) {
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        std::vector<double> x(n);
        std::vector<double> y(n);
        double alpha = rand_double(0.0, 1.0);
        double beta = rand_double(0.0, 1.0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand_double(0.0, 1.0);
            }
            x[i] = rand_double(0.0, 1.0);
            y[i] = rand_double(0.0, 1.0);
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (int trial = 0; trial < ntrial_dgemv; trial++) {
            gemv<double>(alpha, A, x, beta, y);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        double avg_time = duration / static_cast<double>(ntrial_dgemv);
        double FLOPs = (2.0 * n * n + n) / (avg_time * 1e-6);

        std::cout << "n = " << n << ", avg_time = " << avg_time * 1e-6 << " s, FLOPs = " << FLOPs << std::endl;
    }

    return 0;
}
