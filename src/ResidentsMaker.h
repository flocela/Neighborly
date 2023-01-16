#ifndef RESIDENTSMAKER_H
#define RESIDENTSMAKER_H

#include <vector>
#include <memory>
#include "Resident.h"
#include "ResidentsFactory.h"
#include "Color.h"
#include "ResidentsGroupInfo.h"

class ResidentsMaker
{
    public:
        virtual ResidentsGroupInfo makeResidents (
            const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories,
            int maxNumOfResidents,
            int maxNumOfGroupsOfResidents,
            std::vector<BaseColor> colors, // these are the colors that the resident groups can be.
            double allowableMovement
        ) = 0; // TODO should these factories be const? Should this method me const?

        virtual ~ResidentsMaker() = default;
};

#endif