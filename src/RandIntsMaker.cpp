#include "RandIntsMaker.h"
#include <unordered_set>
#include <iostream>

using namespace std;

vector<int> RandIntsMaker::getRandomIntegers(int wellSize, int quantity) const
{   
    if (wellSize < quantity)
    {
        throw invalid_argument("Well size must be at least as large as quantity.");
    }

    // Create vector with numbers from 0 to wellSize - 1.
    vector<int> well(wellSize);

    for (size_t ii=0; ii<well.size(); ++ii)
    {
        well[ii] = ii;
    }

    // Create return vector. Reserve it's size as quantity.
    vector<int> answer{};
    answer.reserve(quantity);

    // Push back quantity number of values from well vector to answer vector.
    int counter = 0;
    while (counter < quantity)
    {   
        // Set randomNum to a random number from the well vector.
        int size = well.size();
        int r = rand() % size;
        int randomNum = well[r];

        // If randomNum from well vector is -1, then try well.size() number of
        // times to select a number from well that is not -1.
        size_t smallCounter = 0;
        while ( smallCounter < well.size() && randomNum == -1 )
        {
            r = rand() % size;
            randomNum = well[r];
            ++smallCounter;
        }

        // If successful and randomNum is not -1, push back randomNum onto answer vector.
        // Replace element at index randomNum in well with -1.
        if (randomNum != -1)
        {
            answer.push_back(randomNum);
            well[r] = -1;
            ++counter;
        }
        // Else if randomNum is still -1, then so many of the elements in well
        // have been replaced with -1 that it is too time consuming to find a
        // non -1 number in well.
        // Remove all -1's from well, and resize well.
        else
        {
            int left = 0;
            for (size_t ii=0; ii<well.size(); ++ii)
            {
                if (well[ii] != -1)
                {
                    well[left] = well[ii];
                    ++left;
                }
            }
            well.resize(left);
        }
    }
    
    return answer;
}