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

void Printer_CMDLine::print(
    std::map<House*, Resident*> residentPerHouse,
    int run,
    std::string title
)
{   

    std::cout << textHelper.createText(residentPerHouse, run, title);
    (void) title;

} 
