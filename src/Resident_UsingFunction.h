#ifndef RESIDENT_USING_FUNCTION_H
#define RESIDENT_USING_FUNCTION_H

#include <memory>
#include "Resident.h"
#include "HappinessFunc.h"

class Resident_UsingFunction : public Resident
{
public:
    Resident_UsingFunction () = delete;
    Resident_UsingFunction (
        int id,
        int groupNumber,
        double allowedMovementDistance,
        double happinessGoal,
        std::unique_ptr<HappinessFunc> happinessFunc,
        std::string name);
    Resident_UsingFunction (const Resident_UsingFunction& obj) = default;
    Resident_UsingFunction (Resident_UsingFunction&& obj) noexcept = default;
    Resident_UsingFunction& operator= (const Resident_UsingFunction& obj) = default;
    Resident_UsingFunction& operator= (Resident_UsingFunction&& obj) noexcept = default;
    ~Resident_UsingFunction() = default; // TODO should be virtual

    std::string toStrBasic () const;

protected:
    double implimentHappiness ( std::set<Resident*> neighbors,  int numOfAdjacentHouses) const override;

private:
    std::unique_ptr<HappinessFunc> _hap_func;
    std::string _name;

};

#endif

//TODO to use as toString for later
/*
std::string Resident_Falling::toStrBasic() const
{
    return "Res_Falling(id, clr, mov, goal, hap0, hap1): (" + 
        std::to_string(getID()) +
        ", " + std::to_string(getGroupId()) +
        ", " + std::to_string(getAllowedMovementDistance()) +
        ", " + std::to_string(getHappinessGoal()) +
        ", " + std::to_string(_happiness_at_zero_diversity) +
        ", " + std::to_string(_happiness_at_one_diversity) +
        ")"; 
}*/