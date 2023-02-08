#ifndef CITYFACTORY_H
#define CITYFACTORY_H

#include "City.h"
#include "UI.h"
#include <map>
#include <string>
#include <memory>

// TODO CityFactory is not checked
class CityFactory
{
    public:
        CityFactory () = default;
        CityFactory (const CityFactory& obj) = default;
        CityFactory (CityFactory&& obj) noexcept = default;
        CityFactory& operator=(const CityFactory& obj) = default;
        CityFactory& operator=(CityFactory&& obj) noexcept = default;
        virtual ~CityFactory() = default;

        virtual std::unique_ptr<City> createCity (
            const UI& ui, 
            int max_width, 
            int max_height
        ) const = 0;

        // returns the name of the type of cities that are produced.
        virtual std::string cityType () const = 0; 
};

#endif