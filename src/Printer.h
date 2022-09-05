#ifndef PRINTER_H
#define PRINTER_H

#include <map>
#include "Resident.h"
#include "Coordinate.h"
#include "City.h"

class Printer
{   public:
        virtual void print(std::unordered_map<const House*, const Resident*> residentPerHouse, int run) = 0;
};

#endif