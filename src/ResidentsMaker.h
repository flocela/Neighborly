#ifndef RESIDENTSMAKER_H
#define RESIDENTSMAKER_H

#include <vector>
#include <memory>
#include "Resident.h"
#include "ResidentsFactory.h"

class ResidentsMaker
{
    public:
        virtual std::vector<std::unique_ptr<Resident>> makeResidents (
            std::vector<ResidentsFactory*> residentsFactories,
            int maxNumOfResidents
        ) = 0; // TODO should these factories be const? Should this method me const?

        virtual std::vector<std::unique_ptr<Resident>> makeBaseResidents (
            std::vector<ResidentsFactory*> residentsFactories,
            int maxNumOfResidents
        ) = 0;
        virtual ~ResidentsMaker() = default;
};

#endif