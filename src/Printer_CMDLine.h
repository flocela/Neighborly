#ifndef PRINTER_CMDLINE_H
#define PRINTER_CMDLINE_H

#include "Printer.h"

class Printer_CMDLine : public Printer
{   
    public:
        void print(
            std::map<House*, Resident*> residentPerHouse,
            int run,
            int totRuns,
            std::string title
        ) override;
        
};

#endif