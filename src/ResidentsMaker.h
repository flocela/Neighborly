#ifndef RESIDENTSMAKER__H
#define RESIDENTSMAKER__H

#include <memory>
#include <vector>
#include "Color.h"
#include "Resident.h"
#include "ResidentsFactory.h"
#include "ResidentsGroupInfo.h"

// Creates residents based on user's choice.
class ResidentsMaker
{

protected:
    ResidentsMaker () = default;
    ResidentsMaker (ResidentsMaker& o) = default;
    ResidentsMaker (ResidentsMaker&& o) noexcept = default;
    ResidentsMaker& operator= (ResidentsMaker& o) = default;
    ResidentsMaker& operator= (ResidentsMaker&& o) noexcept = default;

public:

    virtual ~ResidentsMaker () noexcept = default;
    
    virtual ResidentsGroupInfo makeResidents (
        const UI& ui,
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories,
        int maxNumOfResidents,
        std::vector<BaseColor> colors, // These are the colors that the resident groups can be.
        double allowableMovement
    ) = 0;
};

#endif