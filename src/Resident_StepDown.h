#ifndef Resident_StepDown_H
#define Resident_StepDown_H

#include "Resident.h"
#include "HappinessFunc_StepDown.h"

class Resident_StepDown: public Resident
{
    public:
        Resident_StepDown () = delete;
        Resident_StepDown (
            int id,
            Color color,
            double allowedMovementDistance,
            double happinessGoal,
            double happinessValueAtZeroDiversity,
            double happinessValueAtOneDiversity,
            double diversityWhereDropHappens);
        Resident_StepDown (const Resident_StepDown& obj) = default;
        Resident_StepDown (Resident_StepDown&& obj) noexcept = default;
        Resident_StepDown& operator= (const Resident_StepDown& obj) = default;
        Resident_StepDown& operator= (Resident_StepDown&& obj) noexcept = default;
        ~Resident_StepDown() = default;

        House* findHome(
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesToNeighbors,
            std::map<House*, Resident*> houseToResMap
        ) const override;

        House* findBestHome(
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesToNeighbors,
            std::map<House*, Resident*> houseToResMap
        ) const override;

    private:
        HappinessFunc_StepDown _happiness_func;

    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;
};

#endif