#ifndef RESIDENTSMAKER_H
#define RESIDENTSMAKER_H

#include <vector>
#include <memory>
#include "Resident.h"
#include "ResidentsFactory.h"
#include "Color.h"
#include "ResidentsGroupInfo.h"

// creates residents
class ResidentsMaker
{
    public:
        virtual ResidentsGroupInfo makeResidents (
            const UI& ui,
            const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories,
            int maxNumOfResidents,
            int maxNumOfGroupsOfResidents,
            std::vector<BaseColor> colors, // these are the colors that the resident groups can be.
            double allowableMovement
        ) = 0;

        virtual ~ResidentsMaker() = default;
};

#endif