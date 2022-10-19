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
            int groupNumber,
            double allowedMovementDistance,
            double happinessGoal,
            double happinessValueWithZeroNeighbors,
            double happinessValueAtZeroDiversity,
            double happinessValueAtOneDiversity,
            double diversityWhereRiseHappens);
        Resident_StepUp (const Resident_StepUp& obj) = default;
        Resident_StepUp (Resident_StepUp&& obj) noexcept = default;
        Resident_StepUp& operator= (const Resident_StepUp& obj) = default;
        Resident_StepUp& operator= (Resident_StepUp&& obj) noexcept = default;
        ~Resident_StepUp() = default;

        std::string toStrBasic () const override;

        const House* findHome (
            const House* oldHouse,
            std::map<const House*, std::set<const House*>> openHousesAndTheirAdjacentHouses,
            std::unordered_map<const House*, Resident*> houseToResMap
        ) const override;

        const House* findBestHome (
            const House* oldHouse,
            std::map<const House*, std::set<const House*>> openHousesAndTheirAdjacentHouses,
            std::unordered_map<const House*, Resident*> houseToResMap
        ) const override;

    private:
        double _happiness_with_zero_neighbors;
        double _happiness_at_zero_diversity;
        double _happiness_at_one_diversity;
        double _diversity_where_rise_happens;
        HappinessFunc_StepUp _happiness_func;

    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;

};

#endif