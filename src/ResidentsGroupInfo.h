#ifndef RESIDENTS_GROUP_INFO_H
#define RESIDENTS_GROUP_INFO_H

#include <vector>
#include <unordered_map>
#include <memory>
#include "Resident.h"

class ResidentsGroupInfo
{
public:
    std::vector<std::unique_ptr<Resident>> _residents;
    std::unordered_map<int, BaseColor> _base_color_per_group_num;
};

#endif