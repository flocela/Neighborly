#ifndef PRINTER_CMDLINE_H
#define PRINTER_CMDLINE_H

#include <vector>
#include <unordered_map>
#include "Printer.h"
#include "City.h"

class Printer_CMDLine : public Printer
{   
public:
    Printer_CMDLine (
        int maxNumOfRuns,
        City* cityPtr
    );

    Printer_CMDLine () = delete;
    Printer_CMDLine (const Printer_CMDLine& o) = default;
    Printer_CMDLine (Printer_CMDLine&& o) noexcept = default;
    Printer_CMDLine& operator= (const Printer_CMDLine& o) = default;
    Printer_CMDLine& operator=(Printer_CMDLine&& o) noexcept = default;
    ~Printer_CMDLine () = default;
    
    void print(
        std::unordered_map<const House*, const Resident*> residentPerHouse,
        int run
    ) const override;

private:
    int _max_num_of_runs;
    City* _city_ptr;
    std::unordered_map<const House*, std::set<const House*>> _adj_neighbors;

    // used for printing residents. happy characters per group Id.
    std::vector<char> happyCharacters = {'x', '!', '@', '#', '$', '%'};
        
};

#endif