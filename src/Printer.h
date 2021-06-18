#ifndef PRINTER_H
#define PRINTER_H

#include <map>
#include "Resident.h"
#include "Coordinate.h"
#include "City.h"

class Printer
{   public:
        virtual void print(
                std::map<int, Resident*> residentPerHouse,
                int run,
                int totRuns,
                std::string title) = 0;
};

#endif