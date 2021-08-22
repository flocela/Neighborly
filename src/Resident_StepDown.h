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

        std::string toStrBasic () const override;
        
        House* findHome(
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
            std::map<House*, Resident*> houseToResMap
        ) const override;

        House* findBestHome(
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
            std::map<House*, Resident*> houseToResMap
        ) const override;

    private:
        double _happiness_at_zero_diversity;
        double _happiness_at_one_diversity;
        double _diversity_where_drop_happens;
        HappinessFunc_StepDown _happiness_func;
        
    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;
};

#endif