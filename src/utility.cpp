#include "../include/utility.h"
#include <iostream>
#include <cstdlib>

float rand_float(int min, int max) {
    // generates random float between min and max
    max = max * 10000;
    min = min * 10000;

    return (float)(rand() % (max - min) + min)/(float)10000 ;
}

void initialize_matrix(float* m, const unsigned int rows, const unsigned int cols) {
    // initializes the matrix with random values withing 0 and 100
    for( int i = 0; i < rows; ++i) {
        for( int j = 0; j < cols; ++j) {
            m[j+i*cols] = rand_float(0, 1000);
        }
    }
}

bool checkEqual(const float* M1, const float* M2, const unsigned int rows, const unsigned int cols) {
    // Function to check if the two matrices are equal
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            if (M1[j+i*cols] != M2[j+i*cols]) {
                return false;
            }
        }
    }
    return true;
}

void printMatrix(const float* M, const unsigned int rows, const unsigned int cols) {
    // Function to print the matrix to stdout. Used for debugging
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            std::cout << M[j+i*cols] << " ";
        }
        std::cout << std::endl;
    }
}
