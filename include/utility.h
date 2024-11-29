#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <vector>

float randFloat(int min, int max);

std::vector<std::vector<float>> initializeMatrix(unsigned int rows, unsigned int cols);

void printMatrix(const std::vector<std::vector<float>> &M, unsigned int rows, unsigned int cols);

double computeSpeedup(double serialT, double parallelT);

double computeEfficiency(double Speedup, int numThreads);

bool checkSymCorrectness(bool sym, const std::vector<std::vector<float>> &M, unsigned int rows, unsigned int cols);

bool checkTranspositionCorrectness(const std::vector<std::vector<float>> &M, const std::vector<std::vector<float>> &T, unsigned int rows, unsigned int cols);

void checkCorrect(bool sym, const std::vector<std::vector<float>> &M, const std::vector<std::vector<float>> &T, unsigned int rows, unsigned int cols);

#endif //__UTILITY_H__
