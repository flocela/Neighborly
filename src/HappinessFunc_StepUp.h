#ifndef HAPPINESSFUNC_STEPUP_H
#define HAPPINESSFUNC_STEPUP_H

#include <stdexcept>
#include "HappinessFunc.h"

// this is a step function. the x-axis is diversity. the y-axis is happiness.
// a higher y-value is used from zero to stepDown (on the x-axis). a higher y-value
// is used after stepDown. stepDown is an x-value.
class HappinessFunc_StepUp: public HappinessFunc
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
    // stepUp is an x-value, or a diversity value.
    HappinessFunc_StepUp (double happinessValue);
    HappinessFunc_StepUp () = delete;
    HappinessFunc_StepUp (const HappinessFunc_StepUp& obj) = default;
    HappinessFunc_StepUp (HappinessFunc_StepUp&& obj) noexcept = default;
    HappinessFunc_StepUp& operator=(const HappinessFunc_StepUp& obj) = default;
    HappinessFunc_StepUp& operator=(HappinessFunc_StepUp&& obj) noexcept = default;
    ~HappinessFunc_StepUp() = default;

    HappinessFunc_StepUp (
        double happinessWithZeroNeighbors,
        double happinessAtStart, 
        double happinessAtEnd, 
        double stepUp
    );

    double getMaximumPossibleValue () const;

    double getLeastPossibleValue () const;

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
    double _step_up;
};

#endif