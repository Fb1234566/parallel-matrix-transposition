#ifndef __OPENMP_H__
#define __OPENMP_H__

#include <vector>

std::vector<std::vector<float>> matTransposeOMP (const std::vector<std::vector<float>> &m, unsigned int size);

bool checkSymOMP (const std::vector<std::vector<float>>& m, unsigned int size);

bool checkEqualOMP (const std::vector<std::vector<float>>& m, const std::vector<std::vector<float>>& m1, unsigned int size);

#endif //__OPENMP_H__
