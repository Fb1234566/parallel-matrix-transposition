#include "../include/implicitParallelism.h"
#include <vector>
#include "../include/serial.h"
#include "../include/utility.h"

std::vector<std::vector<float>> matTransposeImp (const std::vector<std::vector<float>> &m, const unsigned int size) {
    /*
        Transposes square matrix
        Parameters:
            - m: matrix to transpose
            - m_transposed: matrix used to save the transposition of m
            - size: size of the square matrix
    */
    std::vector<std::vector<float>> m_transposed (size, std::vector<float>(size));
    #pragma GCC ivdep
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            m_transposed[i][j] = m[j][i];
        }
    }
    return m_transposed;
}

bool checkSymImp (const std::vector<std::vector<float>>& m, const unsigned int size) {
    /*
        Checks if a square matrix is symmetric
        Parameters:
            - m: matrix to check for symmetry
            - size: dimensions of the matrix.
    */

    std::vector<std::vector<float>> m_transposed(size, std::vector<float>(size));
    m_transposed = matTransposeImp(m, size);
    return m==m_transposed;
}
