#include "../include/utility.h"
#include <iostream>
#include <cstdlib>
#include <vector>

float rand_float(int min, int max) {
    // generates random float between min and max
    max = max * 10000;
    min = min * 10000;

    return static_cast<float>(rand() % (max - min) + min)/(float)10000 ;
}

std::vector<std::vector<float>> initialize_matrix(const unsigned int rows, const unsigned int cols) {
    // initializes the matrix with random values withing 0 and 100
    std::vector<std::vector<float>> m(rows, std::vector<float>(cols));
    for( int i = 0; i < rows; ++i) {
        for( int j = 0; j < cols; ++j) {
            m[i][j] = rand_float(0, 1000);
        }
    }
    return m;
}

void printMatrix(const std::vector<std::vector<float>> &M, const unsigned int rows, const unsigned int cols) {
    // Function to print the matrix to stdout. Used for debugging
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double computeSpeedup(const double serialT, const double parallelT) {
    return (serialT / parallelT);
}

double computeEfficiency(const double Speedup, const int numThreads) {
    return (Speedup/numThreads) * 100;
}
