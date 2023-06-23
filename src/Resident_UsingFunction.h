#ifndef RESIDENT_USING_FUNCTION_H
#define RESIDENT_USING_FUNCTION_H

#include <memory>
#include "Resident.h"
#include "HappinessFunc.h"

// Uses the HappinessFunc given in the constructor to determine the resident happiness.
class Resident_UsingFunction : public Resident
{
protected:
    Resident_UsingFunction (const Resident_UsingFunction& obj) = default;
    Resident_UsingFunction (Resident_UsingFunction&& obj) noexcept = default;
    Resident_UsingFunction& operator= (const Resident_UsingFunction& obj) = default;
    Resident_UsingFunction& operator= (Resident_UsingFunction&& obj) noexcept = default;

public:
    Resident_UsingFunction (
        int id,
        int groupNumber,
        double allowedMovementDistance,
        double happinessGoal,
        std::unique_ptr<HappinessFunc> happinessFunc);
    Resident_UsingFunction () = delete;
    virtual ~Resident_UsingFunction () noexcept = default;
    double getMaximumPossibleHappiness () const;
    double getLeastPossibleHappiness () const;

protected:
    double implimentHappiness (
        const std::unordered_set<const Resident*>& neighbors,
        int numOfAdjacentHouses) const override;
    
    std::string implimentToStrBasic () const override; 

private:
    std::unique_ptr<HappinessFunc> _hap_func;

};

#endif