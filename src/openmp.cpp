#include <vector>
#include "../include/openmp.h"
#include <omp.h>

std::vector<std::vector<float>> matTransposeOMP (const std::vector<std::vector<float>> &m, const unsigned int size) {
    /*
        Transposes square matrix
        Parameters:
            - m: matrix to transpose
            - m_transposed: matrix used to save the transposition of m
            - size: size of the square matrix
    */
    std::vector<std::vector<float>> m_transposed (size, std::vector<float>(size));
    #pragma omp parallel for collapse(2)
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            m_transposed[i][j] = m[j][i];
        }
    }
    return m_transposed;
}

bool checkSymOMP (const std::vector<std::vector<float>>& m, const unsigned int size) {
    /*
        Checks if a square matrix is symmetric
        Parameters:
            - m: matrix to check for symmetry
            - size: dimensions of the matrix.
    */
    int sum = 0;
    #pragma omp parallel
    {
        #pragma omp for collapse(2) reduction(+:sum)
        for(unsigned int i = 0; i < size; i++) {
            for(unsigned int j = 0; j < size; j++) {
                sum += m[i][j] == m[j][i];
            }
        }
    }
    return (sum == (size*size));
}
