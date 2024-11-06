#include <iostream>
#include "../include/utility.h"
#include <cstdlib>

#define SIZE 4 // size of the matrix

float M [SIZE][SIZE]; // original matrix
float M_transposed [SIZE][SIZE]; // transposed matrix

void matTranspose (const float* m, float* m_transposed, const unsigned int size) {
    // transposes the matrix
    std::cout<<"Transposing matrix..."<<std::endl;
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            m_transposed[j+i*size] = m[i+j*size];
        }
    }
    std::cout<<"Finished transposing!"<<std::endl;
}

bool checkSym (float* m, const unsigned int size) {
    // checks that the matrix is symmetric
    std::cout<<"Checking symmetry matrix..."<<std::endl;
    matTranspose(reinterpret_cast<float *>(M), reinterpret_cast<float *>(M_transposed), SIZE);
    if (checkEqual(reinterpret_cast<float *>(M), reinterpret_cast<float *>(M_transposed), SIZE, SIZE)) {
        std::cout<<"Matrix is symmetric!"<<std::endl;
        return true;
    }
    std::cout<<"Matrix is not symmetric!"<<std::endl;
    return false;
}



int main() {
    srand(time(NULL));
    initialize_matrix(reinterpret_cast<float *>(M), SIZE, SIZE);
    bool res = checkSym((float*) M, SIZE);
    return 0;
}