#ifndef RESIDENT_CUSTOMIABLE_H
#define RESIDENT_CUSTOMIZABLE_H

#include <memory>
#include "Resident.h"
#include "HappinessFunc.h"

// Uses the HappinessFunc given in the constructor to determine the resident happiness.
class Resident_Customizable : public Resident
{

protected:

    Resident_Customizable (const Resident_Customizable& obj) = default;
    Resident_Customizable (Resident_Customizable&& obj) noexcept = default;
    Resident_Customizable& operator= (const Resident_Customizable& obj) = default;
    Resident_Customizable& operator= (Resident_Customizable&& obj) noexcept = default;

public:
    Resident_Customizable (
        int id,
        int groupNumber,
        double allowedMovementDistance,
        double happinessGoal,
        std::unique_ptr<HappinessFunc> happinessFunc);
    Resident_Customizable () = delete;
    virtual ~Resident_Customizable () noexcept = default;
    
    double getMaximumPossibleHappiness () const;
    double getLeastPossibleHappiness () const;

    std::unique_ptr<const ResidentTemplate> getTemplate () const override;

protected:
    double implimentHappiness (
        const std::unordered_set<const Resident*>& neighbors,
        int numOfAdjacentHouses) const override;
    
    std::string implimentGetType () const override; 

private:
    std::unique_ptr<HappinessFunc> _hap_func;

};

#endif