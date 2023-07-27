#ifndef RANDINTSMAKER_H
#define RANDINTSMAKER_H

#include <vector>

// Produces a number of non-repeating numbers.
class RandIntsMaker
{
public:
    std::vector<int> getRandomIntegers(int wellSize, int quantity) const;
};

#endif