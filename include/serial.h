#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <vector>

std::vector<std::vector<float>> matTranspose (const std::vector<std::vector<float>> &m, unsigned int size);

bool checkSym (const std::vector<std::vector<float>>& m, unsigned int size);

#endif //__SERIAL_H__
