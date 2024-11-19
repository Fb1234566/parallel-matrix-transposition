#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <vector>

float rand_float(int min, int max);

std::vector<std::vector<float>> initialize_matrix(unsigned int rows, unsigned int cols);

void printMatrix(const std::vector<std::vector<float>> &M, unsigned int rows, unsigned int cols);

double computeSpeedup(double serialT, double parallelT);

double computeEfficiency(double Speedup, int numThreads);

#endif //__UTILITY_H__
