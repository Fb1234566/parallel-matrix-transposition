#include <cmath>
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
    bool size_fixed = false;
    int min_size, max_size;
    int size = -1;

    /* Take input parameters from shell
       Parameters:
           -h -> show help message
           -s <size> -> set the matrix size
           -m <size> -> set the minimum size used for iteration (2^m)
           -M <size> -> set the maximum size used for iteration (2^M)
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
                    min_size = std::stoi(argv[i]);
                    max_size = min_size;
                    size_fixed = true;
                    if (min_size < 1) {
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
            if (strcmp(argv[i-1], "-m")==0){
                if (size_fixed) {
                    std::cerr << "-m flag cannot be used with -s parameter" << std::endl;
                    return -1;
                }
                try {
                    min_size = std::stoi(argv[i]);
                    if (min_size < 1) {
                        std::cerr << "Invalid size!" << std::endl;
                        return -1;
                    }
                } catch (...) {
                    std::cerr << "Invalid size!" << std::endl;
                    return -1;
                }
                command = false;
            }
            if (strcmp(argv[i-1], "-M")==0){
                if (size_fixed) {
                    std::cerr << "-M flag cannot be used with -s parameter" << std::endl;
                    return -1;
                }
                try {
                    max_size = std::stoi(argv[i]);
                    if (max_size < 1) {
                        std::cerr << "Invalid size!" << std::endl;
                        return -1;
                    }
                } catch (...) {
                    std::cerr << "Invalid size!" << std::endl;
                    return -1;
                }
                command = false;
            }
        }
        else {
            if (i == argc) {
                break;
            }
            if(argv[i][0] == '-') { // check if currently parsed arg is a command
                if((argv[i][1] == 's') || (argv[i][1] == 'h')|| (argv[i][1] == 'm')|| (argv[i][1] == 'M')) {
                    command = true;
                }
                else { // if command is valid
                    std::cerr << "Invalid argument: " << argv[i] << std::endl;
                    return -1;
                }
            }
        }
    }

    // files where results are saved
    std::ofstream resSerial;
    std::ofstream resImpParallelism;
    std::ofstream resOpenMP;


    resSerial.open("export/serial.csv", std::ios::app);
    if (!resSerial.is_open()) {
        std::cerr << "Could not open file export/serial.csv" << std::endl;
        return -1;
    }
    resSerial << "iteration, time, size" << std::endl;

    resImpParallelism.open("export/implicit_parallelism.csv", std::ios::app);
    if (!resImpParallelism.is_open()) {
        std::cerr << "Could not open file export/implicit_parallelism.csv" << std::endl;
        return -1;
    }
    resImpParallelism << "iteration, time, size" << std::endl;

    resOpenMP.open("export/openMP.csv", std::ios::app);
    if (!resOpenMP.is_open()) {
        std::cerr << "Could not open file export/openMP.csv" << std::endl;
        return -1;
    }
    resOpenMP << "iteration, time, speedup, efficiency, size, threads" << std::endl;

    std::cout << "*********************************" << std::endl;
    std::cout << "* Parallel Matrix Transposition *" << std::endl;
    std::cout << "*********************************" << std::endl;
    for (int k=min_size; k<=max_size; k++) {
        size = static_cast<int>(std::pow(2.0, k));
        /* Setup matrix to be transposed */
        std::vector<std::vector<float>> M (size, std::vector<float>(size));
        std::vector<std::vector<float>> T (size, std::vector<float>(size));
        M = initializeMatrix(size, size);
        std::cout << "Size: " << size << " : " << std::endl;
        /*---------Serial section---------*/
        std::cout << "[1] Parallel section:" << std::endl;
        bool sym = false;
        double sum_serial = 0.0;
        for(int i = 0; i < 10; i++) {
            const double t0_ser = omp_get_wtime();
            sym = checkSym(M, size);
            T = matTranspose(M, size);
            const double t1_ser = omp_get_wtime();
            sum_serial+= t1_ser - t0_ser;
            resSerial << i <<", " << t1_ser - t0_ser << ", " << size << std::endl;
        }
        if (sym) {
            std::cout<<"Matrix is symmetric!"<<std::endl;
        }
        else {
            std::cout<<"Matrix is not symmetric!"<<std::endl;
        }
        std::cout << "Average time: " << sum_serial/10.0 << " sec" << std::endl;

        /*---------Implicit parallelism section---------*/
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "[2] Implicit parallelization section:" << std::endl;
        bool sym_impl = false;
        double sum_impl = 0.0;
        for (unsigned int i = 0; i < 10; i++) {
            const clock_t t0_impl = clock();
            sym_impl = checkSymImp(M, size);
            T = matTransposeImp(M, size);
            const clock_t t1_impl = clock();
            sum_impl += (static_cast<double>(t1_impl - t0_impl)) / CLOCKS_PER_SEC;
            resImpParallelism << i << ", " << (static_cast<double>(t1_impl - t0_impl)) / CLOCKS_PER_SEC << ", " << size << std::endl;
        }
        if (sym_impl) {
            std::cout<<"Matrix is symmetric!"<<std::endl;
        }
        else {
            std::cout<<"Matrix is not symmetric!"<<std::endl;
        }

        std::cout << "Time: " << sum_impl/10.0<< " sec" << std::endl;

        /*---------OMP parallel section---------*/
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "[3]OpenMP section:" << std::endl;
        bool sym_omp = false;
        for (int t = 1; t < 16; t++) { // repeat experiment using different number of threads
            std::cout << "Threads: " << t << std::endl;
            double sum_omp = 0.0;
            double sum_speedup = 0.0;
            double sum_efficiency = 0.0;
            for (unsigned int i = 0; i < 10; i++) {
                const double t0_omp = omp_get_wtime();
                sym_omp = checkSymOMP(M, size, t);
                T = matTransposeOMP(M, size, t);
                const double t1_omp = omp_get_wtime();
                sum_omp += (t1_omp - t0_omp);
                double speedup = computeSpeedup(sum_serial/10.0, (t1_omp - t0_omp));
                double efficiency = computeEfficiency(speedup, t);
                sum_speedup += speedup;
                sum_efficiency += efficiency;
                resOpenMP << i << ", " << (t1_omp - t0_omp) << ", " << speedup << ", " << efficiency << ", " << size << ", " << t << std::endl;

            }
            if (sym_omp) {
                std::cout<<"Matrix is symmetric!"<<std::endl;
            }
            else {
                std::cout<<"Matrix is not symmetric!"<<std::endl;
            }

            std::cout << "Time: " << sum_omp/10.0<< " sec" << std::endl;
            std::cout << "Speedup: " << sum_speedup/10.0 << std::endl;
            std::cout << "Efficiency: " << sum_efficiency/10.0 << std::endl;
            std::cout << "++++++++++++++++++++++++++++++++++" << std::endl;
        }

    }
    resSerial.close();
    resImpParallelism.close();
    resOpenMP.close();
    return 0;
}