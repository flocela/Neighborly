#ifndef PRINTER_H
#define PRINTER_H

#include <unordered_map>

#include "House.h"
#include "Resident.h"
#include "RunMetrics.h"

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

    virtual void print (const RunMetrics* runMetrics) const = 0;
};

#endif