#ifndef RESIDENTSFACTORY_H
#define RESIDENTSFACTORY_H

#include <memory>
#include <vector>
#include "Color.h"
#include "Resident.h"
#include "UI.h"

class ResidentsFactory
{
protected:
    ResidentsFactory () = default;
    ResidentsFactory (const ResidentsFactory& o) = default;
    ResidentsFactory (ResidentsFactory&& o) noexcept = default;
    ResidentsFactory& operator= (const ResidentsFactory& o) = default;
    ResidentsFactory& operator= (ResidentsFactory&& o) noexcept = default;

public:
    virtual ~ResidentsFactory () noexcept = default;
    
    virtual std::vector<std::unique_ptr<Resident>> createResidents(
        const UI& ui,
        int firstID, 
        int count,
        double happinessGoal,
        double allowedMovement,
        int groupNumber,
        BaseColor baseColor
    )const = 0;

    virtual std::string residentType () const= 0;
    
    virtual std::string toString () = 0;
};

#endif