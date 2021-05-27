#ifndef HAPPINESSFUNC_FLAT_H
#define HAPPINESSFUNC_FLAT_H

#include "HappinessFunc.h"

// Always returns the same happiness value, no matter the neighbors.
class HappinessFunc_Flat: public HappinessFunc
{
    public:
        // HappinessFunc_Flat has an x-axis of Diversity and
        // a y-axis of Happiness. Both axes range from 0.0 to 1.0.
        // @happinessValue is the y-axis Happiness at all points of the x-axis.
        // An exception is thrown if happinessValue is 
        // not in the range 0.0 to 1.0.
        HappinessFunc_Flat (double happinessValue);
        HappinessFunc_Flat () = delete;
        HappinessFunc_Flat (const HappinessFunc_Flat& obj) = default;
        HappinessFunc_Flat (HappinessFunc_Flat&& obj) noexcept = default;
        HappinessFunc_Flat& operator=(const HappinessFunc_Flat& obj) = default;
        HappinessFunc_Flat& operator=(HappinessFunc_Flat&& obj) noexcept = default;
        ~HappinessFunc_Flat() override = default;
        
        double getHappiness( int tot_num_of_possible_neighbors, 
                             int num_of_like_neighbors, 
                             int num_of_diff_neighbors) const override;
    private:
        double _result;
};

#endif