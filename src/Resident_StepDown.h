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
            double happinessValueAtZeroDiversity,
            double happinessValueAtOneDiversity,
            double diversityWhereDropHappens);
        Resident_StepDown (const Resident_StepDown& obj) = default;
        Resident_StepDown (Resident_StepDown&& obj) noexcept = default;
        Resident_StepDown& operator= (const Resident_StepDown& obj) = default;
        Resident_StepDown& operator= (Resident_StepDown&& obj) noexcept = default;
        ~Resident_StepDown() = default;

        std::string toStrBasic () const override;
        
        const House* findHome(
            const House* oldHouse,
            std::map<const House*, std::set<const House*>> openHousesAndTheirAdjacentHouses,
            std::unordered_map<const House*, Resident*> houseToResMap
        ) const override;

        const House* findBestHome(
            const House* oldHouse,
            std::map<const House*, std::set<const House*>> openHousesAndTheirAdjacentHouses,
            std::unordered_map<const House*, Resident*> houseToResMap
        ) const override;

    private:
        double _happiness_with_zero_neighbors;
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