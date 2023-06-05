#ifndef PRINTER_CMDLINE_H
#define PRINTER_CMDLINE_H

#include <vector>
#include <unordered_map>

#include "City.h"
#include "Color.h"
#include "Printer.h"

class Printer_CMDLine : public Printer
{

public:
    Printer_CMDLine (
        std::unordered_map<int, BaseColor> baseColorsPerGroupid,
        int maxNumOfRuns,
        const City* cityPtr
    );

    Printer_CMDLine () = delete;
    Printer_CMDLine (const Printer_CMDLine& o) = default;
    Printer_CMDLine (Printer_CMDLine&& o) noexcept = default;
    Printer_CMDLine& operator= (const Printer_CMDLine& o) = default;
    Printer_CMDLine& operator= (Printer_CMDLine&& o) noexcept = default;
    ~Printer_CMDLine () = default;
    
    void print(
        const RunMetrics* runMetrics,
        int run
    ) const override;

private:
    std::unordered_map<int, BaseColor> _base_colors_per_groupid;

    int _max_num_of_runs;

    const City* _city_ptr;

    // used for printing residents. happy characters per group Id.
    std::vector<char> happyCharacters = {'x', '!', '@', '#', '$', '%'};
        
};

#endif