#ifndef HAPPINESSFUNC_RISING_H
#define HAPPINESSFUNC_RISING_H

#include "HappinessFunc.h"

class HappinessFunc_Rising: public HappinessFunc
{
    public:
        // HappinessFunc_Rising has an x-axis of Diversity and
        // a y-axis of Happiness. Both axes range from 0.0 to 1.0.
        // @happinessAtZeroDiversity is the y-axis Happiness when
        // Diversity is 0.0.
        // @happinessAtOneDiversity is the y-axis happiness when
        // Diversity is 1.0.
        // Exception is thrown @if happinessAtZeroDiversity or 
        // hapinessAtOneDiversity is not in range.
        // Exception is thrown if happinessAtZeroDiversity is 
        // larger than happiness at OneDiversity.
        HappinessFunc_Rising ( double happinessAtZeroDiversity,
                              double happinessAtOneDiversity);
        HappinessFunc_Rising () = delete;
        HappinessFunc_Rising (const HappinessFunc_Rising& obj) = default;
        HappinessFunc_Rising (HappinessFunc_Rising&& obj) noexcept = default;
        HappinessFunc_Rising& operator=(const HappinessFunc_Rising& obj) = default;
        HappinessFunc_Rising& operator=(HappinessFunc_Rising&& obj) noexcept = default;
        ~HappinessFunc_Rising() override = default;  

        double getHappiness ( int tot_num_of_possible_neighbors, 
                              int num_of_like_neighbors, 
                              int num_of_diff_neighbors) const override;
    private:
        double _happiness_at_zero_diversity;
        double _happiness_at_one_diversity;
};

#endif