#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <fstream>
#include "func.hh"

int main() {
    // Initialization
    int n = 2048;
    int ntrial = 1024;
    std::vector<int> block_sizes = {1, 2, 4, 8, 16, 32, 64};
    int block_len = block_sizes.size();
    std::srand(std::time(0));
    std::ofstream output_file("output2.txt");

    // Allocate memory
    std::vector<double> x(n);
    std::vector<double> y(n);

    // Assign alpha: random number between (1, 10)
    double alpha = rand_double(1.0, 10.0);

    // Assign random values to x and y also between (1, 10)
    for (int i = 0; i < n; i++) {
        x[i] = rand_double(1.0, 10.0);
        y[i] = rand_double(1.0, 10.0);
    }

    // Go through each block size:
    for (int k = 0; k < block_len; k++) {
        int block_size = block_sizes[k];
        auto start = std::chrono::high_resolution_clock::now();

        for (int j = 0; j < ntrial; j++) {
            daxpy_unroll(alpha, x, y, n, block_size);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        double avg_time = duration / static_cast<double>(ntrial);
        double FLOPs = (2 * n) / (avg_time * 1e-6);

        std::cout << "for block size = " << block_size << ", average time = " << avg_time * 1e-6 << " s, FLOPs = " << FLOPs << std::endl;
        output_file << block_size << ", " << FLOPs << std::endl;
    }

    output_file.close();

    return 0;
}
