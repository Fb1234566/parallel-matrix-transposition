#include <vector>
#include "../include/serial.h"

#include <omp.h>

std::vector<std::vector<float>> matTranspose (const std::vector<std::vector<float>> &m, const unsigned int size) {
    /*
        Transposes square matrix
        Parameters:
            - m: matrix to transpose
            - m_transposed: matrix used to save the transposition of m
            - size: size of the square matrix
    */
    omp_set_dynamic(0);
    omp_set_num_threads(1);
    std::vector<std::vector<float>> m_transposed (size, std::vector<float>(size));
#pragma omp parallel
    {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            m_transposed[i][j] = m[j][i];
        }
    }
    }
    return m_transposed;
}

bool checkSym (const std::vector<std::vector<float>>& m, const unsigned int size) {
    /*
        Checks if a square matrix is symmetric
        Parameters:
            - m: matrix to check for symmetry
            - size: dimensions of the matrix.
    */
    omp_set_dynamic(0);
    omp_set_num_threads(1);
    int res = 0;
    #pragma omp parallel
    {
        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; j++) {
                res += m[i][j] == m[j][i];
            }
        }
    }
    return res == (size*size);
}
