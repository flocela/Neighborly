#ifndef RESIDENTSMAKER_H
#define RESIDENTSMAKER_H

#include <vector>
#include <memory>
#include "Resident.h"
#include "ResidentsFactory.h"
#include "Color.h"

class ResidentsMaker
{
    public:
        virtual std::vector<std::unique_ptr<Resident>> makeResidents (
            std::vector<ResidentsFactory*> residentsFactories,
            int maxNumOfResidents,
            std::set<BaseColor> colors, // these are the colors that the resident groups can be.
            double allowableMovement
        ) = 0; // TODO should these factories be const? Should this method me const?

        virtual ~ResidentsMaker() = default;
};

#endif