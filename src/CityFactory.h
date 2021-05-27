#ifndef CITYFACTORY_H
#define CITYFACTORY_H

#include "City.h"
#include "UI.h"
#include <map>
#include <string>
#include <memory>

class CityFactory
{
    public:
        CityFactory () = default;
        CityFactory (const CityFactory& obj) = default;
        CityFactory (CityFactory&& obj) noexcept = default;
        CityFactory& operator=(const CityFactory& obj) = default;
        CityFactory& operator=(CityFactory&& obj) noexcept = default;
        virtual ~CityFactory() = default;

        virtual std::unique_ptr<City> createCity (UI& ui) = 0;
        virtual std::string toString () = 0;
};

#endif