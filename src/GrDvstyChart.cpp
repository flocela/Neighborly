#include "GrDvstyChart.h"

using namespace std;

void GrDvstyChart::print (
    unordered_map<const Resident*, const House*> housePerResident,
    unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer
) const
{
    // for each groupid, will need the number of residents in group
    // and the number of disparate neighbors.
    unordered_map<int, int> numOfResidentsPerGroupId;
    unordered_map<int, int> numOfDiffNeighborsPerGroupId;

    for (auto& pair : _b_color_per_groupId)
    {
        numOfDiffNeighborsPerGroupId[pair.first] = 0;
        numOfResidentsPerGroupId[pair.first] = 0;
    }

    for (pair<const Resident*, const House*> ii : housePerResident)
    {
        const Resident* resident = ii.first;
        const House* residentHouse = ii.second;
        int residentGroupId = resident->getGroupId();

        set<const House*> housesAdjToRes = _adj_neighbors.at(residentHouse);

        for (const House* adjacentHouse : housesAdjToRes)
        {
            // if adjacent house is not empty
            if (residentPerHouse.find(adjacentHouse) != residentPerHouse.end())
            {
                // adjacent resident's groupId
                int adj_res_groupId = (residentPerHouse.at(adjacentHouse))->getGroupId();
                if (adj_res_groupId != residentGroupId)
                {
                    numOfDiffNeighborsPerGroupId[adj_res_groupId] +=1;
                }
            }
        }

        numOfResidentsPerGroupId[residentGroupId] += 1;
    }

    // the diversity for a resident is the number of disperate neighbors the resident has.
    // the Point's y value is the average diversity for the residents in the group.
    // the Point's x value is the run number.

    vector<Point> points{};
    for (auto pair : numOfResidentsPerGroupId)
    {
        int groupId = pair.first;
        int numOfResidentsInGroup = pair.second;
        
        if (numOfResidentsInGroup == 0)
        {
            continue;
        }

        double averageNumOfDiffNeighbors = 
            (double)numOfDiffNeighborsPerGroupId[groupId]/numOfResidentsInGroup;

        Color groupColor = _colorrs_map.at(_b_color_per_groupId.at(groupId)).at(Mood::neutral)._color;
        points.push_back(Point((double)run, averageNumOfDiffNeighbors, groupColor));
    }
    
    if (!_key_has_printed)
    {
        _key->print(renderer);
        _key_has_printed = true;
    }
    if (!_title_has_printed)
    {
        _title->print(renderer);
        _title_has_printed = true;
    }
    
    _plot->print(points, false, renderer);
}

int GrDvstyChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrDvstyChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}