#ifndef PRINTER_H
#define PRINTER_H

#include "City.h"
#include "Coordinate.h"
#include "renderer.h"
#include "Resident.h"

class Printer
{   
public:
     virtual void print (
         std::unordered_map<const House*, const Resident*> residentPerHouse,
         int run) const = 0;
};

#endif