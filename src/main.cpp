#include <iostream>
#include <fstream>
#include "../include/utility.h"
#include "../include/serial.h"
#include "../include/implicitParallelism.h"
#include "../include/openmp.h"
#include <cstdlib>
#include <cstring>
#include <vector>
#include <omp.h>

int main(int argc, char* argv[]) {
    srand(time(nullptr)); // sets the random seed
    bool command = false; // used to check if a command has been passed via parameters
    int size = -1;

    /* Take input parameters from shell
       Parameters:
           -h -> show help message
           -s <size> -> set the matrix size
    */
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

    /* Setup matrix to be transposed */
    std::vector<std::vector<float>> M (size, std::vector<float>(size));
    std::vector<std::vector<float>> T (size, std::vector<float>(size));
    M = initialize_matrix(size, size);
    // files where results are saved
    std::ofstream resSerial;
    std::ofstream resImpParallelism;
    std::ofstream resOpenMP;

    std::cout << "Parallel Matrix Transposition" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    /*---------Serial section---------*/
    std::cout << "[1] Parallel section:" << std::endl;
    resSerial.open("export/serial.csv");
    if (!resSerial.is_open()) {
        std::cerr << "Could not open file export/serial.csv" << std::endl;
        return -1;
    }
    bool sym = false;
    double sum_serial = 0.0;
    resSerial << "iteration, time" << std::endl;
    for(int i = 0; i < 10; i++) {
        const clock_t t0_seq = clock();
        sym = checkSym(M, size);
        T = matTranspose(M, size);
        const clock_t t1_seq = clock();
        sum_serial+=(static_cast<double>(t1_seq - t0_seq)) / CLOCKS_PER_SEC;
        resSerial << i <<", " << (static_cast<double>(t1_seq - t0_seq)) / CLOCKS_PER_SEC << std::endl;
    }
    resSerial.close();
    if (sym) {
        std::cout<<"Matrix is symmetric!"<<std::endl;
    }
    else {
        std::cout<<"Matrix is not symmetric!"<<std::endl;
    }
    std::cout << "Average time: " << sum_serial/10.0 << " sec" << std::endl;

    /*---------Implicit parallelism section---------*/
    std::cout << "*************************************" << std::endl;
    std::cout << "[2] Implicit parallelization section:" << std::endl;
    bool sym_impl = false;
    double sum_impl = 0.0;
    resImpParallelism.open("export/implicit_parallelism.csv");
    if (!resImpParallelism.is_open()) {
        std::cerr << "Could not open file export/implicit_parallelism.csv" << std::endl;
        return -1;
    }
    resImpParallelism << "iteration, time" << std::endl;
    for (unsigned int i = 0; i < 10; i++) {
        const clock_t t0_impl = clock();
        sym_impl = checkSymImp(M, size);
        T = matTransposeImp(M, size);
        const clock_t t1_impl = clock();
        sum_impl += (static_cast<double>(t1_impl - t0_impl)) / CLOCKS_PER_SEC;
        resImpParallelism << i << ", " << (static_cast<double>(t1_impl - t0_impl)) / CLOCKS_PER_SEC << std::endl;
    }
    resImpParallelism.close();

    if (sym_impl) {
        std::cout<<"Matrix is symmetric!"<<std::endl;
    }
    else {
        std::cout<<"Matrix is not symmetric!"<<std::endl;
    }


    std::cout << "Time: " << sum_impl/10.0<< " sec" << std::endl;
    /*---------OMP parallel section---------*/
    std::cout << "*************************************" << std::endl;
    std::cout << "[2]OpenMP section:" << std::endl;
    bool sym_omp = false;
    double sum_omp = 0.0;
    resOpenMP.open("export/openMP.csv");
    if (!resOpenMP.is_open()) {
        std::cerr << "Could not open file export/openMP.csv" << std::endl;
        return -1;
    }
    resOpenMP << "iteration, time" << std::endl;
    for (unsigned int i = 0; i < 10; i++) {
        const double t0_omp = omp_get_wtime();
        sym_omp = checkSymOMP(M, size);
        T = matTransposeOMP(M, size);
        const double t1_omp = omp_get_wtime();
        sum_omp += (t1_omp - t0_omp);
        resOpenMP << i << ", " << (t1_omp - t0_omp) << std::endl;
    }
    resOpenMP.close();
    if (sym_omp) {
        std::cout<<"Matrix is symmetric!"<<std::endl;
    }
    else {
        std::cout<<"Matrix is not symmetric!"<<std::endl;
    }


    std::cout << "Time: " << sum_omp/10.0<< " sec" << std::endl;
    return 0;
}