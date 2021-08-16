#ifndef HAPPINESSFUNC_STEPUP_H
#define HAPPINESSFUNC_STEPUP_H

#include "HappinessFunc.h"

class HappinessFunc_StepUp: public HappinessFunc
{
    public:
        // HappinessFunc_StepUp has an x-axis of Diversity and a y-axis
        // of Happiness. Both axes range from 0.0 to 1.0.
        // This describes a step function. For example:
        // HappinessFunctionStepUp(.50, .90, .75) makes
        // a function that stays constant at a happiness value of 0.5 from
        // diversity 0.0 to 0.7499.. 
        // Then jumps at 0.75 diversity to a value of 0.9.
        // So it has a constant 0.9 happiness from diversity 0.75 
        // to 1.0.
        HappinessFunc_StepUp (double happinessValue);
        HappinessFunc_StepUp () = delete;
        HappinessFunc_StepUp (const HappinessFunc_StepUp& obj) = default;
        HappinessFunc_StepUp (HappinessFunc_StepUp&& obj) noexcept = default;
        HappinessFunc_StepUp& operator=(const HappinessFunc_StepUp& obj) = default;
        HappinessFunc_StepUp& operator=(HappinessFunc_StepUp&& obj) noexcept = default;
        ~HappinessFunc_StepUp() override = default;

        HappinessFunc_StepUp (double happinessAtZeroDiversity, 
                             double happinessAtOneDiversity, 
                             double diversityWhereRiseHappens);
        double getHappiness( int tot_num_of_possible_neighbors, 
                             int num_of_like_neighbors, 
                             int num_of_diff_neighbors) const override;

    private:
        double _happiness_at_zero_diversity;
        double _happiness_at_one_diversity;
        double _diversity_where_rise_happens;
};

#endif