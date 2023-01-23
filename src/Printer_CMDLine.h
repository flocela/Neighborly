#ifndef PRINTER_CMDLINE_H
#define PRINTER_CMDLINE_H

#include "Printer.h"
#include "TextHelper.h"

class Printer_CMDLine : public Printer
{   
    public:
        Printer_CMDLine (
            int maxNumOfRuns,
            City* cityPtr
        );
        
        void print(
            std::unordered_map<const House*, const Resident*> residentPerHouse,
            int run
        ) const override;

    private:
        int _max_num_of_runs;
        City* _city_ptr;
        TextHelper textHelper;
        
};

#endif