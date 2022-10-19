#ifndef RESIDENT_RISING_H
#define RESIDENT_RISING_H

#include "Resident.h"
#include "HappinessFunc_Rising.h"

class Resident_Rising: public Resident
{
    public:
        Resident_Rising () = delete;
        Resident_Rising (
            int id,
            int groupNumber,
            double allowedMovementDistance,
            double happinessGoal,
            double happinessWithZeroNeighbors,
            double happinessValueAtZeroDiversity,
            double happinessValueAtOneDiversity);
        Resident_Rising (const Resident_Rising& obj) = default;
        Resident_Rising (Resident_Rising&& obj) noexcept = default;
        Resident_Rising& operator= (const Resident_Rising& obj) = default;
        Resident_Rising& operator= (Resident_Rising&& obj) noexcept = default;
        ~Resident_Rising() = default;

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
        HappinessFunc_Rising _happiness_func;
        
    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;
};

#endif