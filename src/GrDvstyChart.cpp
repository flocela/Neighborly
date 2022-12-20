#include "GrDvstyChart.h"

void GrDvstyChart::print (
    std::unordered_map<const Resident*, const House*> housePerResident,
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer
)
{
    std::unordered_map<int, int> num_of_residents_Per_groupId;
    std::unordered_map<int, int> num_of_diff_neighbors_Per_group_id;
    for (auto& pair : _colors)
    {
        num_of_diff_neighbors_Per_group_id[pair.first] = 0;
        num_of_residents_Per_groupId[pair.first] = 0;
    }

    for (std::pair<const Resident*, const House*> ii : housePerResident)
    {
        const Resident* res = ii.first;
        const House*    res_house = ii.second;
        int             res_groupId = res->getGroupNumber();

        std::set<const House*> adj_houses_to_res = _adj_neighbors[res_house];

        for (const House* adjHouse : adj_houses_to_res)
        {
            // if adjHouse is not empty
            if (residentPerHouse.find(adjHouse) != residentPerHouse.end())
            {
                // adjacent resident's groupId
                int adj_res_groupId = (residentPerHouse.at(adjHouse))->getGroupNumber();
                if (adj_res_groupId != res_groupId)
                {
                    num_of_diff_neighbors_Per_group_id[adj_res_groupId] +=1;
                }
            }
        }

        num_of_residents_Per_groupId[res_groupId] += 1;
        
    }

    std::unordered_map<Color, std::vector<Point>> pointsPerColor;
    for (auto pair : num_of_residents_Per_groupId)
    {
        int groupId = pair.first;
        int num_of_res_in_group = pair.second;

        double averageNumOfDiffNeighbors = 
            (double)num_of_diff_neighbors_Per_group_id[groupId]/num_of_res_in_group; // TODO count in group shoudl not be be zero
       
        Color c = _colorrs_map[_colors[groupId]][Mood::neutral]._color;
        pointsPerColor.insert({
            c,
            std::vector<Point>( 1, Point((double)run, averageNumOfDiffNeighbors, c) )
        });
    }
    
    _title->print(renderer);
    _plot->print(pointsPerColor, false, renderer);
    _key->print(renderer);
}

std::set<const Resident*> GrDvstyChart::getResidentsInHouses (
    std::set<const House*> houses,
    const std::unordered_map<const House*, const Resident*> residentPerHouse
)
{
    std::set<const Resident*> residents;
    for (const House* house : houses)
    {
        if (residentPerHouse.find(house) != residentPerHouse.end())
        {   
            residents.insert(residentPerHouse.at(house));
        }
    }

    return residents;
}

int GrDvstyChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrDvstyChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}