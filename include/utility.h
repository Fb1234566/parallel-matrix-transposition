#ifndef __UTILITY_H__
#define __UTILITY_H__

float rand_float(int min, int max);

void initialize_matrix(float* m, unsigned int rows, unsigned int cols);

bool checkEqual(const float* M1, const float* M2, unsigned int rows, unsigned int cols);

void printMatrix(const float* M, unsigned int rows, unsigned int cols);

#endif //__UTILITY_H__
