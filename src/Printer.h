#ifndef PRINTER_H
#define PRINTER_H

#include <unordered_map>

#include "House.h"
#include "Resident.h"

class Printer
{   
public:
    virtual void print (
         std::unordered_map<const House*, const Resident*> residentPerHouse,
         int run) const = 0;
};

#endif