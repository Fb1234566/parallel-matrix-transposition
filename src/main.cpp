#include <iostream>
#include "../include/utility.h"
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>

std::vector<std::vector<float>> matTranspose (const std::vector<std::vector<float>> &m, const unsigned int size) {
/*
    Transposes square matrix
    Parameters:
        - m: matrix to transpose
        - m_transposed: matrix used to save the transposition of m
        - size: size of the square matrix
*/
    std::vector<std::vector<float>> m_transposed (size, std::vector<float>(size));
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            m_transposed[i][j] = m[j][i];
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

    std::vector<std::vector<float>> m_transposed(size, std::vector<float>(size));
    m_transposed = matTranspose(m, size);
    return m==m_transposed;
}



int main(int argc, char* argv[]) {
    srand(time(nullptr)); // sets the random seed
    bool command = false; // used to check if a command has been passed via parameters
    int size = -1;

    // take input parameters
    if (argc == 1) {
        // checks if there are no arguments
        std::cerr << "Missing arguments!" << std::endl;
        return -1;
    }

    // iterate through argv
    for(unsigned int i = 0; i<=argc; i++) {
        if (command) { // check if prev argument is a command
            if (strcmp(argv[i-1], "-s")==0) { // do action if command is found
                // check if the input is an actual number
                try {
                    size = std::stoi(argv[i]);
                    if (size < 1) {
                        std::cerr << "Invalid size!" << std::endl;
                        return -1;
                    }
                } catch (...) {
                    std::cerr << "Invalid size!" << std::endl;
                    return -1;
                }
                command = false;
            }
            if (strcmp(argv[i-1], "-h")==0) {
                std::cout << "Usage: " << std::endl;
                std::cout << "\t-s <size>: Size of the square matrix to be transposed" << std::endl;
                std::cout << "\t-h: Print this help message" << std::endl;
                return 0;
            }
        }
        else {
            if (i == argc) {
                break;
            }
            if(argv[i][0] == '-') { // check if currently parsed arg is a command
                if((argv[i][1] == 's') || (argv[i][1] == 'h')) {
                    command = true;
                }
                else { // if command is valid
                    std::cerr << "Invalid argument: " << argv[i] << std::endl;
                    return -1;
                }
            }
        }
    }

    if (size == -1) {
        std::cerr << "Size not set: pass -s to set the size of the matrix" << std::endl;
        return -1;
    }

    std::vector<std::vector<float>> M (size, std::vector<float>(size));
    M = initialize_matrix(size, size);
    std::cout << "Parallel Matrix Transposition" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "[1] Parallel section:" << std::endl;
    const clock_t t0_seq = clock();
    const bool sym = checkSym(M, size);
    const clock_t t1_seq = clock();
    if (sym) {
        std::cout<<"Matrix is symmetric!"<<std::endl;
    }
    else {
        std::cout<<"Matrix is not symmetric!"<<std::endl;
    }

    std::cout << "Time: " << (static_cast<double>(t1_seq - t0_seq)) / CLOCKS_PER_SEC << " sec" << std::endl;
    return 0;
}