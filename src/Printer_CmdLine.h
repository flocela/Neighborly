#ifndef PRINTER_CMDLINE_H
#define PRINTER_CMDLINE_H

#include <vector>
#include <unordered_map>

#include "City.h"
#include "CityPrinter.h"
#include "Color.h"
#include "Printer.h"
#include "ResidentTemplate.h"

class Printer_CmdLine : public Printer
{
public:
    Printer_CmdLine (
        const CityPrinter& cityPrinter,
        const std::unordered_map<int, BaseColor>& baseColorsPerGroupid,
        const std::unordered_map<int, std::unique_ptr<const ResidentTemplate>>& resTemplatePerGroupId,
        int maxNumOfRuns,
        int seedNumber,
        std::string simulatorString
    );

    Printer_CmdLine () = delete;
    Printer_CmdLine (const Printer_CmdLine& o) = default;
    Printer_CmdLine (Printer_CmdLine&& o) noexcept = default;
    Printer_CmdLine& operator= (const Printer_CmdLine& o) = default;
    Printer_CmdLine& operator= (Printer_CmdLine&& o) noexcept = default;
    ~Printer_CmdLine () noexcept = default;
    
    void print(const RunMetrics* runMetrics) const override;

    void lastPrint () override;

private:
    const CityPrinter& _city_printer;
    const std::unordered_map<int, BaseColor>& _base_colors_per_groupid;
    const std::unordered_map<int, std::unique_ptr<const ResidentTemplate>>& _res_templates_per_group_id;
    int _max_num_of_runs;
    int _seed_number;
    std::string _simulator_name;

    // Used for printing residents. These are the happy characters per group Id, where
    // the group id is the vector index.
    std::vector<char> happyCharacters = {'x', '!', '@', '#', '$', '%'};
        
};

#endif