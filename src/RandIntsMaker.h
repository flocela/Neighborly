#ifndef RANDINTSMAKER_H
#define RANDINTSMAKER_H

#include <vector>

// Produces a number of non-repeating numbers.
class RandIntsMaker
{

public:

    // A well of integers is created, from zero to wellSize-1.
    // Then quantity number of integers are taken from the well (and not replaced).
    // The integers that are taken are returned as a vector.
    std::vector<int> getRandomIntegers(int wellSize, int quantity) const;

};

#endif