#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <vector>

float rand_float(int min, int max);

std::vector<std::vector<float>> initialize_matrix(unsigned int rows, unsigned int cols);

bool checkEqual(const std::vector<std::vector<float>> &M1, const std::vector<std::vector<float>> &M2, unsigned int rows, unsigned int cols);

void printMatrix(const std::vector<std::vector<float>> &M, unsigned int rows, unsigned int cols);

#endif //__UTILITY_H__