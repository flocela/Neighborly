#ifndef HAPPINESSFUNCTION_H
#define HAPPINESSFUNCTION_H

// HappinessFunc has an x-axis of Diversity and a y-axis of Happiness.
// Both axes range from 0.0 to 1.0.
class HappinessFunc
{
public:

    virtual double calcHappiness (
        int tot_num_of_possible_neighbors, 
        int num_of_like_neighbors, 
        int num_of_diff_neighbors) const = 0;
    
    virtual std::string toStrBasic () const = 0;

};

#endif