#ifndef Resident_StepUp_H
#define Resident_StepUp_H

#include "Resident.h"
#include "HappinessFunc_StepUp.h"

class Resident_StepUp: public Resident
{
    public:
        Resident_StepUp () = delete;
        Resident_StepUp (
            int id,
            Color color,
            double allowedMovementDistance,
            double happinessGoal,
            double happinessValueAtZeroDiversity,
            double happinessValueAtOneDiversity,
            double diversityWhereRiseHappens);
        Resident_StepUp (const Resident_StepUp& obj) = default;
        Resident_StepUp (Resident_StepUp&& obj) noexcept = default;
        Resident_StepUp& operator= (const Resident_StepUp& obj) = default;
        Resident_StepUp& operator= (Resident_StepUp&& obj) noexcept = default;
        ~Resident_StepUp() = default;

        

        House* findHome (
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesToNeighbors,
            std::map<House*, Resident*> houseToResMap
        ) const override;

        House* findBestHome (
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesToNeighbors,
            std::map<House*, Resident*> houseToResMap
        ) const override;

    private:
        HappinessFunc_StepUp _happiness_func;

    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;

};

#endif