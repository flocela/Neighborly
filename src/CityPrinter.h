#ifndef CITY_PRINTER_H
#define CITY_PRINTER_H

#include <unordered_map>
#include "City.h"
#include "Color.h"

class CityPrinter
{

public:
    CityPrinter (const City* city);
    CityPrinter() = delete;
    CityPrinter (const CityPrinter& o) = default;
    CityPrinter (CityPrinter&& o) noexcept = default;
    CityPrinter& operator= (const CityPrinter& o) = default;
    CityPrinter& operator= (CityPrinter&& o) noexcept = default;

    std::string print (std::unordered_map<int, char> characterPerAddress) const;

private:
    const City* _city;

};

#endif