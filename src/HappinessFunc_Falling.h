#ifndef HAPPINESSFUNC_FALLING_H
#define HAPPINESSFUNC_FALLING_H

#include "HappinessFunc.h"

class HappinessFunc_Falling: public HappinessFunc
{
    public:
        HappinessFunc_Falling (double happinessAtZeroPercentDiversity,
                              double happinessAt100PercentDiversity);
        HappinessFunc_Falling () = delete;
        HappinessFunc_Falling (const HappinessFunc_Falling& obj) = default;
        HappinessFunc_Falling (HappinessFunc_Falling&& obj) noexcept = default;
        HappinessFunc_Falling& operator=(const HappinessFunc_Falling& obj) = default;
        HappinessFunc_Falling& operator=(HappinessFunc_Falling&& obj) noexcept = default;
        ~HappinessFunc_Falling() override = default;
        double getHappiness( int tot_num_of_possible_neighbors, 
                             int num_of_like_neighbors, 
                             int num_of_diff_neighbors) const override;
    private:
        double _happiness_at_zero_percent_diversity;
        double _happiness_at_hundred_percent_diversity;
};

#endif