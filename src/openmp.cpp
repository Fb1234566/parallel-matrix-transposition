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

    std::vector<std::vector<float>> m_transposed(size, std::vector<float>(size));
    m_transposed = matTransposeOMP(m, size);
    return checkEqualOMP(m_transposed, m, size);
}

bool checkEqualOMP (const std::vector<std::vector<float>>& m, const std::vector<std::vector<float>>& m1, unsigned int size) {
    /*
     Checks if two matrices are equal
     Parameters:
        -m: first matrix
        -m1: second matrix
        -size: size of the two matrices
    */
    int final = 0;
    int res = 0;
    #pragma omp parallel
        {
        #pragma omp for collapse(2) reduction(+:res)
        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; j++) {
                res += m[i][j] == m1[i][j];
            }
        }


        #pragma  omp critical
            final += res;
    }

    return final == (size*size);
}

