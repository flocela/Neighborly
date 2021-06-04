#ifndef PRINTER_CMDLINE_H
#define PRINTER_CMDLINE_H

#include "Printer.h"

class Printer_CMDLine : public Printer
{   
    public:
        void print(
            std::map<int, Resident*> residentPerHouse,
            int run,
            int totRuns,
            std::string title
        ) override;
        void printResidents(std::map<int, Resident*> housePerResident,
                            std::map<int, Coordinate> coordinatePerHouse,
                            int run,
                            int totRuns,
                            std::string title) override;
        
};

#endif