#ifndef HAPPINESSFUNC_FLAT_H
#define HAPPINESSFUNC_FLAT_H

#include <stdexcept>
#include "HappinessFunc.h"

// Always returns the same happiness value, no matter the neighbors.
class HappinessFunc_Flat: public HappinessFunc
{
public:
    // x-axis is Diversity, range is 0.0 to 1.0 inclusive.
    // y-axis is Happiness, range is 0.0 to 100.0 inclusive.
    // happinessValue is the y-axis Happiness at all points of the x-axis.
    // an exception is thrown if happinessValue is not in the range 0.0 to 100.0.
    // when total number of neighbors is zero, diversity is undefined.
    // happinessWithNoNeighbors returns a y-value for when total neighbors is zero.
    HappinessFunc_Flat (double happinessWithNoNeighbors, double happinessValue);
    HappinessFunc_Flat () = delete;
    HappinessFunc_Flat (const HappinessFunc_Flat& obj) = default;
    HappinessFunc_Flat (HappinessFunc_Flat&& obj) noexcept = default;
    HappinessFunc_Flat& operator=(const HappinessFunc_Flat& obj) = default;
    HappinessFunc_Flat& operator=(HappinessFunc_Flat&& obj) noexcept = default;
    ~HappinessFunc_Flat() = default;
    
    double getMaximumPossibleValue () const;

    double getLeastPossibleValue () const;

    double calcHappiness(
        int tot_num_of_possible_neighbors, 
        int num_of_like_neighbors, 
        int num_of_diff_neighbors) const override;

    std::string toStrBasic () const override;

private:
    // on the y-axis (happiness values)
    double _happ_with_no_neighbors;
    double _flat_happiness_val;
};

#endif