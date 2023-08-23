#ifndef RESIDENTS_GROUP_INFO__H
#define RESIDENTS_GROUP_INFO__H

#include "Resident.h"
#include "ResidentTemplate.h"

#include <memory>
#include <unordered_map>
#include <vector>

struct ResidentsGroupInfo
{
    
public:

    std::unordered_map<int, BaseColor> _base_color_per_group_num{};
    std::unordered_map<int, std::unique_ptr<const ResidentTemplate>> _res_template_per_group_id{};
    std::vector<std::unique_ptr<Resident>> _residents{};

};

#endif