#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <fstream>
#include "func.hh"

int main() {
    // Initialization
    int ntrial = 1000;
    std::srand(std::time(nullptr));
    std::ofstream output_file("output.txt");

    // Loop from 2 to 1024 with increment 1
    for (int n = 2; n <= 1024; n += 2) {
        // Allocate memories for the pointer:
        std::vector<double> x(n);
        std::vector<double> y(n);

        // Assign alpha: random number between (1, 10)
        double alpha = rand_double(1.0, 10.0);
       
        // Assign random values to x and y also between (1, 10)
        for (int i = 0; i < n; i++) {
            x[i] = rand_double(1.0, 10.0);
            y[i] = rand_double(1.0, 10.0);
        }

        // Initialize the time
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < ntrial; j++) {
            daxpy(alpha, x, y, n);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        // Find the FLOPs
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        double avg_time = duration / static_cast<double>(ntrial);
        double FLOPs = (2.0 * n) / (avg_time * 1e-6); // f(n) = 2 * n scaler multiplication and addition
        std::cout << "for n = " << n << ", average time = " << avg_time * 1e-6 << " s, FLOPs = " << FLOPs << std::endl;

        output_file << n << ", " << FLOPs << std::endl;
    }

    output_file.close();
    return 0;
}
