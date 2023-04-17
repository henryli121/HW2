#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <fstream>
#include "func.hh"

int main() {
    //initialization
    int ntrial = 3;
    std::srand(std::time(0));
    std::ofstream output_file("output4.txt");

    //allocate memeories:
    for (int n = 2; n <= 1024; n++) {
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        std::vector<std::vector<double>> B(n, std::vector<double>(n));
        std::vector<std::vector<double>> C(n, std::vector<double>(n));
        double alpha = rand_double(1.0, 10.0);
        double beta = rand_double(1.0, 10.0);

        //assign values to matrices
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand_double(1.0, 10.0);
                B[i][j] = rand_double(1.0, 10.0);
                C[i][j] = rand_double(1.0, 10.0);
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (int trial = 0; trial < ntrial; trial++) {
            dgemm(alpha, A, B, beta, C, n);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        double avg_time = duration / static_cast<double>(ntrial);
        double FLOPs = (2.0 * n * n * n + 3.0 * n * n) / (avg_time * 1e-6);

        std::cout << "n = " << n << ", avg_time = " << avg_time * 1e-6 << " s, FLOPs = " << FLOPs << std::endl;
        output_file << n << ", " << FLOPs << std::endl;
    }

    output_file.close();
    return 0;
}