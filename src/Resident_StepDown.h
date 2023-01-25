#ifndef RESIDENT_STEPDOWN_H
#define RESIDENT_STEPDOWN_H

#include "Resident.h"
#include "HappinessFunc_StepDown.h"

class Resident_StepDown: public Resident
{
    public:
        Resident_StepDown () = delete;
        Resident_StepDown (
            int id,
            int groupNumber,
            double allowedMovementDistance,
            double happinessGoal,
            double happinessWithZeroNeighbors,
            double highHappinessValue,
            double lowHappinessValue,
            double diversityWhereDropHappens);
        Resident_StepDown (const Resident_StepDown& obj) = default;
        Resident_StepDown (Resident_StepDown&& obj) noexcept = default;
        Resident_StepDown& operator= (const Resident_StepDown& obj) = default;
        Resident_StepDown& operator= (Resident_StepDown&& obj) noexcept = default;
        ~Resident_StepDown() = default;

        std::string toStrBasic () const override;

    private:
        double _happiness_with_zero_neighbors;
        double _high_happiness_value;
        double _low_hapiness_value;
        double _diversity_drop;
        HappinessFunc_StepDown _happiness_func;
        
    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;
};

#endif