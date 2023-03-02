#ifndef RESIDENTS_GROUP_INFO_H
#define RESIDENTS_GROUP_INFO_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "Resident.h"

class ResidentsGroupInfo
{
public:

    std::unordered_map<int, BaseColor> _base_color_per_group_num;
    std::vector<std::unique_ptr<Resident>> _residents;

};

#endif