#ifndef TEXTHELPER_H
#define TEXTHELPER_H

#include "City.h"
#include "Resident.h"
#include "House.h"

class TextHelper
{
    public:
        TextHelper (
            int maxNumOfRuns,
            City* cityPtr
        ):  _max_num_of_runs{maxNumOfRuns},
            _city_ptr{cityPtr}
        {}

        std::string createText (
            std::map<const House*, Resident*> residentPerHouse,
            int run
        ) const;
    private:
        int _max_num_of_runs;
        City* _city_ptr;
};

#endif