#ifndef RESIDENTSFACTORY_H
#define RESIDENTSFACTORY_H

#include <vector>
#include <memory>
#include "Color.h"
#include "Resident.h"
#include "UI.h"

class ResidentsFactory
{
    public:
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