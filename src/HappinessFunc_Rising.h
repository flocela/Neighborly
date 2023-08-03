#ifndef HAPPINESSFUNC_RISING_H
#define HAPPINESSFUNC_RISING_H

#include <stdexcept>
#include "HappinessFunc.h"

// Happiness increases as diversity increases.
class HappinessFunc_Rising: public HappinessFunc
{

public:

    // x-axis is Diversity, range is [0.0 to 1.0].
    // y-axis is Happiness, range is [0.0 to 100.0].
    // An exception is thrown if happiness at zero diversity is larger than or equal
    // to happiness at one diversity, or if either value is not in the range [0.0, 100.0].
    // When total number of neighbors is zero, diversity is undefined.
    // happinessWithNoNeighbors is the y-value corresponding to when the total
    // number of neighbors is zero.
    HappinessFunc_Rising (
        double happinessWithNoNeighbors,
        double happinessAtZeroDiversity,
        double happinessAtOneDiversity
    );
    HappinessFunc_Rising () = delete;
    HappinessFunc_Rising (const HappinessFunc_Rising& obj) = default;
    HappinessFunc_Rising (HappinessFunc_Rising&& obj) noexcept = default;
    HappinessFunc_Rising& operator=(const HappinessFunc_Rising& obj) = default;
    HappinessFunc_Rising& operator=(HappinessFunc_Rising&& obj) noexcept = default;
    ~HappinessFunc_Rising () noexcept = default;  

    double getLargestValue () const;

    double getSmallestValue () const;

    double calcHappiness (
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