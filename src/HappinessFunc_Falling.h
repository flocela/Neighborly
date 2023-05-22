#ifndef HAPPINESSFUNC_FALLING_H
#define HAPPINESSFUNC_FALLING_H

#include <stdexcept>
#include "HappinessFunc.h"

// Happiness decreases as diversity increases.
class HappinessFunc_Falling: public HappinessFunc
{
public:
    // x-axis is diversity (as a percentage, number of disparate neighbors/ total number
    // of neighbors), range is 0.0 to 1.0 inclusive.
    // y-axis is Happiness, range is 0.0 to 100.0 inclusive.
    // an exception is thrown if @happinessZeroDiversity is less than or equal
    // to @happiness100Diversity, or if either value is not in the range
    // 0.0 to 100.0 inclusive.
    // when total number of neighbors is zero, diversity is undefined.
    // happinessWithNoNeighbors is the y-value corresponding to total neighbors is zero.
    HappinessFunc_Falling (
        double happinessWithNoNeighbors, 
        double happinessAtZeroDiversity,
        double happinessAt100Diversity);
    HappinessFunc_Falling () = delete;
    HappinessFunc_Falling (const HappinessFunc_Falling& obj) = default;
    HappinessFunc_Falling (HappinessFunc_Falling&& obj) noexcept = default;
    HappinessFunc_Falling& operator=(const HappinessFunc_Falling& obj) = default;
    HappinessFunc_Falling& operator=(HappinessFunc_Falling&& obj) noexcept = default;
    ~HappinessFunc_Falling() = default;

    double getLargestValue () const;

    double getSmallestValue () const;

    double calcHappiness( 
        int tot_num_of_possible_neighbors, 
        int num_of_like_neighbors, 
        int num_of_diff_neighbors) const override;

    std::string toStrBasic () const override;
private:
    double _happ_with_no_neighbors;
    double _happ_at_zero_diversity;
    double _happ_at_100_diversity;
};

#endif