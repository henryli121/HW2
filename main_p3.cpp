#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <fstream>
#include "refBLAS.hpp"

int main() {
    int ntrial = 100;
    std::srand(std::time(0));
    std::ofstream output_file("output3.txt");

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
        for (int trial = 0; trial < ntrial; trial++) {
            dgemv<double>(alpha, A, x, beta, y);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        double avg_time = duration / static_cast<double>(ntrial);
        double FLOPs = (2.0 * n * n + n) / (avg_time * 1e-6);

        std::cout << "n = " << n << ", avg_time = " << avg_time * 1e-6 << " s, FLOPs = " << FLOPs << std::endl;
        output_file << n << ", " << FLOPs << std::endl;
    }

    output_file.close();
    return 0;
}
