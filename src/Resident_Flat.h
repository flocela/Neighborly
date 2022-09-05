#ifndef Resident_Flat_H
#define Resident_Flat_H

#include "Resident.h"
#include "HappinessFunc_Flat.h"

class Resident_Flat: public Resident
{
    public:
        Resident_Flat () = delete;
        Resident_Flat (
            int id,
            int groupNumber,
            double allowedMovementDistance,
            double happinessGoal,
            double happinessValue);
        Resident_Flat (const Resident_Flat& obj) = default;
        Resident_Flat (Resident_Flat&& obj) noexcept = default;
        Resident_Flat& operator= (const Resident_Flat& obj) = default;
        Resident_Flat& operator= (Resident_Flat&& obj) noexcept = default;
        ~Resident_Flat() = default;

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
        double _happiness_val;
        HappinessFunc_Flat _happiness_func;
    
    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;
};

#endif