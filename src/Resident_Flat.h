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
            Color color,
            double allowedMovementDistance,
            double happinessGoal,
            bool   happyAtGoal,
            double happinessValue);
        Resident_Flat (const Resident_Flat& obj) = default;
        Resident_Flat (Resident_Flat&& obj) noexcept = default;
        Resident_Flat& operator= (const Resident_Flat& obj) = default;
        Resident_Flat& operator= (Resident_Flat&& obj) noexcept = default;
        ~Resident_Flat() = default;

        double getHappiness (
            std::vector<Color> neighbors,
            int numOfAdjacentHouses
        ) const override;
        private:
        HappinessFunc_Flat _happiness_func;
};

#endif