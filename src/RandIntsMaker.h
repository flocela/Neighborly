#ifndef RANDINTSMAKER__H
#define RANDINTSMAKER__H

#include <vector>

// Produces a number of non-repeating numbers.
class RandIntsMaker
{

public:

    // A well of integers is created, from zero to wellSize-1.
    // Then quantity number of integers are taken from the well (and not replaced)
    // and placed in a vector. That vector is returned.
    std::vector<int> getRandomIntegers(int wellSize, int quantity) const;

};

#endif