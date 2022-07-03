#ifndef RESIDENT_FALLING_H
#define RESIDENT_FALLING_H

#include "Resident.h"
#include "HappinessFunc_Falling.h"

class Resident_Falling: public Resident
{
    public:
        Resident_Falling () = delete;
        Resident_Falling (
            int id,
            int groupNumber,
            double allowedMovementDistance,
            double happinessGoal,
            double happinessValueAtZeroDiversity,
            double happinessValueAtOneDiversity);
        Resident_Falling (const Resident_Falling& obj) = default;
        Resident_Falling (Resident_Falling&& obj) noexcept = default;
        Resident_Falling& operator= (const Resident_Falling& obj) = default;
        Resident_Falling& operator= (Resident_Falling&& obj) noexcept = default;
        ~Resident_Falling() = default;

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
        HappinessFunc_Falling _happiness_func;
        
    protected:
        double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const override;
};

#endif