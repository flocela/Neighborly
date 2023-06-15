#include "RandomIntegers.h"
#include <unordered_set>
#include <iostream>

using namespace std;

vector<int> RandomIntegers::getRandomIntegers(int wellSize, int quantity) const
{   
    if (wellSize < quantity)
    {
        throw invalid_argument("Well size must be at least as large as quantity.");
    }

    // Create vector with numbers from zero to wellSize - 1.
    vector<int> well(wellSize);

    for (size_t ii=0; ii<well.size(); ++ii)
    {
        well[ii] = ii;
    }

    vector<int> answer{};
    int counter = 0;

    while (counter < quantity)
    {   
        int size = well.size();
        int r = rand() % size;
        int randomNum = well[r];

        size_t smallCounter = 0;
        while ( smallCounter < well.size() && randomNum == -1 )
        {
            r = rand() % size;
            randomNum = well[r];
            ++smallCounter;
        }

        if (randomNum != -1)
        {
            answer.push_back(randomNum);
            well[r] = -1;
            ++counter;
        }
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