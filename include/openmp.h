#ifndef __OPENMP_H__
#define __OPENMP_H__

#include <vector>

std::vector<std::vector<float>> matTransposeOMP (const std::vector<std::vector<float>> &m, unsigned int size, int threads);

bool checkSymOMP (const std::vector<std::vector<float>>& m, unsigned int size, int threads);

#endif //__OPENMP_H__
