#ifndef CITYMAKER_H
#define CITYMAKER_H

#include <vector>
#include <memory>
#include "City.h"
#include "CityFactory.h"

class CityMaker
{
    public:
        virtual std::unique_ptr<City> makeCity (std::vector<CityFactory*> cityFactories) = 0;
        
};

#endif