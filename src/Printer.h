#ifndef PRINTER__H
#define PRINTER__H

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

    virtual ~Printer () noexcept = default;

    virtual void print (const RunMetrics* runMetrics) const = 0;

    // Allows printer to do items after last print.
    virtual void lastPrint () = 0;
};

#endif