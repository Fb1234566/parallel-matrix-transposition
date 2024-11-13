#ifndef __IMPLICITPARALLELISM_H__
#define __IMPLICITPARALLELISM_H__

#include <vector>

std::vector<std::vector<float>> matTransposeImp (const std::vector<std::vector<float>> &m, unsigned int size);

bool checkSymImp (const std::vector<std::vector<float>>& m, unsigned int size);

#endif //__IMPLICITPARALLELISM_H__
