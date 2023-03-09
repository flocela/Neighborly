#ifndef PRINTER_H
#define PRINTER_H

#include <unordered_map>

#include "House.h"
#include "Resident.h"

class Printer
{
protected:
    Printer () = default;
    Printer (const Printer& o) = default;
    Printer (Printer&& o) noexcept = default;
    Printer& operator= (const Printer& o) = default;
    Printer& operator= (Printer&& o) noexcept = default;
    
public:
    virtual ~Printer () = default;

    virtual void print (
         std::unordered_map<const House*, const Resident*> residentPerHouse,
         int run) const = 0;
};

#endif