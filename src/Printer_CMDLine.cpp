#include "Printer_CMDLine.h"

#include <vector>
#include <algorithm>

Printer_CMDLine::Printer_CMDLine (
    int maxNumofRuns,
    City* cityPtr
):  _max_num_of_runs{maxNumofRuns},
    _city_ptr{cityPtr},
    textHelper{maxNumofRuns,cityPtr}
{}

void Printer_CMDLine::print(std::unordered_map<const House*, const Resident*> residentPerHouse, int run)
{   
    (void)residentPerHouse;
    (void)run;
    //std::cout << textHelper.createText(residentPerHouse, run);

} 
