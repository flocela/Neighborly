#ifndef HAPPINESSFUNC_FALLING_H
#define HAPPINESSFUNC_FALLING_H

#include <stdexcept>
#include "HappinessFunc.h"

// Happiness decreases as diversity increases.
class HappinessFunc_Falling: public HappinessFunc
{

public:

    // x-axis is diversity, calculated as number of disparate neighbors/ total number of neighbors.
    // The range is [0.0, 1.0].
    // y-axis is Happiness and has a range of [0.0, 100.0].
    // An exception is thrown if happiness at 0.0 diversity is less than or equal
    // to happiness at 1.0 diversity, or if either happiness value is not in the range
    // 0.0 to 100.0 inclusive.
    // When total number of neighbors is zero, diversity is undefined.
    // happinessWithNoNeighbors is the y-value corresponding to when total neighbors is zero.
    HappinessFunc_Falling (
        double happinessWithNoNeighbors, 
        double happinessAtZeroDiversity,
        double happinessAtOneDiversity);
    HappinessFunc_Falling () = delete;
    HappinessFunc_Falling (const HappinessFunc_Falling& obj) = default;
    HappinessFunc_Falling (HappinessFunc_Falling&& obj) noexcept = default;
    HappinessFunc_Falling& operator=(const HappinessFunc_Falling& obj) = default;
    HappinessFunc_Falling& operator=(HappinessFunc_Falling&& obj) noexcept = default;
    ~HappinessFunc_Falling () noexcept = default;

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
    double _happ_at_one_diversity;
};

#endif