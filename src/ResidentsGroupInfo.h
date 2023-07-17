#ifndef RESIDENTS_GROUP_INFO_H
#define RESIDENTS_GROUP_INFO_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "Resident.h"
#include "ResidentTemplate.h"

struct ResidentsGroupInfo
{
public:

    std::unordered_map<int, BaseColor> _base_color_per_group_num{};
    std::unordered_map<int, std::unique_ptr<ResidentTemplate>> _resident_template_per_group_id{};
    std::vector<std::unique_ptr<Resident>> _residents{};

};

#endif