#ifndef HAPPINESSFUNC_STEPDOWN__H
#define HAPPINESSFUNC_STEPDOWN__H

#include <stdexcept>
#include "HappinessFunc.h"

// This is a step function. The x-axis is diversity. The y-axis is happiness.
// A higher y-value is used from zero upto-and-including the stepDown location (on the x-axis).
// A lower y-value is used after the stepDown location. stepDown is an x-value.
class HappinessFunc_StepDown: public HappinessFunc
{

public:

    // x-axis is Diversity, range is [0.0 to 1.0].
    // y-axis is Happiness, range is [0.0 to 100.0].
    // An exception is thrown if happinesAtStart is less than or equal
    // to happinessAtEnd, or if either value is not in the range
    // 0.0 to 100.0 inclusive.
    // When the total number of neighbors is zero, diversity is undefined.
    // happinessWithZeroNeighbors is the y-value corresponding to having no neighbors.
    // happinessWithZeroNeighbors, happinessAtStart, happinessAtEnd are y-values.
    // stepDown is an x-value (a diversity value).
    HappinessFunc_StepDown (
        double happinessWithZeroNeighbors, 
        double happinessAtStart, // higher happiness value
        double happinessAtEnd,   // lower happiness value 
        double stepDown
    );
    HappinessFunc_StepDown () = delete;
    HappinessFunc_StepDown (const HappinessFunc_StepDown& obj) = default;
    HappinessFunc_StepDown (HappinessFunc_StepDown&& obj) noexcept = default;
    HappinessFunc_StepDown& operator=(const HappinessFunc_StepDown& obj) = default;
    HappinessFunc_StepDown& operator=(HappinessFunc_StepDown&& obj) noexcept = default;
    ~HappinessFunc_StepDown () noexcept = default;                       

    double getLargestValue () const;

    double getSmallestValue () const;

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