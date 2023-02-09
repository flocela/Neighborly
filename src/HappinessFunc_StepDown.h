#ifndef HAPPINESSFUNC_STEPDOWN_H
#define HAPPINESSFUNC_STEPDOWN_H

#include <stdexcept>
#include "HappinessFunc.h"

// this is a step function. the x-axis is diversity. the y-axis is happiness.
// the y-value is flat from zero to stepDown (on the x-axis). it is flat
// but lower after stepDown. stepDown is an x-value.
class HappinessFunc_StepDown: public HappinessFunc
{
public:
    // x-axis is Diversity, range is 0.0 to 1.0 inclusive.
    // y-axis is Happiness, range is 0.0 to 100.0 inclusive.
    // an exception is thrown if @happinessAtStart is less than or equal
    // to @happinessAtEnd, or if either value is not in the range
    // 0.0 to 100.0 inclusive.
    // when total number of neighbors is zero, diversity is undefined.
    // happinessWithNoNeighbors is the y-value corresponding to total neighbors is zero.
    // happinessWithZeroNeighbors, happinessAtStart, happinessAtEnd are y-values, or happiness values.
    // stepDown is an x-value, or a diversity value.
    HappinessFunc_StepDown (
        double happinessWithZeroNeighbors, 
        double happinessAtStart, 
        double happinessAtEnd, 
        double stepDown
    );
    HappinessFunc_StepDown () = delete;
    HappinessFunc_StepDown (const HappinessFunc_StepDown& obj) = default;
    HappinessFunc_StepDown (HappinessFunc_StepDown&& obj) noexcept = default;
    HappinessFunc_StepDown& operator=(const HappinessFunc_StepDown& obj) = default;
    HappinessFunc_StepDown& operator=(HappinessFunc_StepDown&& obj) noexcept = default;
    ~HappinessFunc_StepDown() override = default;                       

    double calcHappiness(
        int tot_num_of_possible_neighbors, 
        int num_of_like_neighbors, 
        int num_of_diff_neighbors) const override;
    
    std::string toStrBasic () const override;

private:
    // on the y-axis (happiness values)
    double _happ_with_zero_neighbors;
    double _happ_at_start;
    double _happ_at_end;

     // on the x-value (diversity value)   
    double _step_down;
};

#endif