#include "GrDvstyChart.h"

using namespace std;

void GrDvstyChart::print (
    unordered_map<const Resident*, const House*> housePerResident,
    unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer
)
{
    unordered_map<int, int> numOfResidentsPerGroupid;
    unordered_map<int, int> numOfDiffNeighborsPerGroupid;

    for (auto& pair : _colors)
    {
        numOfDiffNeighborsPerGroupid[pair.first] = 0;
        numOfResidentsPerGroupid[pair.first] = 0;
    }

    for (pair<const Resident*, const House*> ii : housePerResident)
    {
        const Resident* res = ii.first;
        const House* resHouse = ii.second;
        int resGroupid = res->getGroupNumber();

        set<const House*> housesAdjToRes = _adj_neighbors[resHouse];

        for (const House* adjHouse : housesAdjToRes)
        {
            // if adjHouse is not empty
            if (residentPerHouse.find(adjHouse) != residentPerHouse.end())
            {
                // adjacent resident's groupId
                int adj_res_groupId = (residentPerHouse.at(adjHouse))->getGroupNumber();
                if (adj_res_groupId != resGroupid)
                {
                    numOfDiffNeighborsPerGroupid[adj_res_groupId] +=1;
                }
            }
        }

        numOfResidentsPerGroupid[resGroupid] += 1;
    }

    unordered_map<Color, vector<Point>> pointsPerColor;
    for (auto pair : numOfResidentsPerGroupid)
    {
        int groupId = pair.first;
        int numOfResInGroup = pair.second;
        
        if (numOfResInGroup == 0)
        {
            continue;
        }

        double averageNumOfDiffNeighbors = 
            (double)numOfDiffNeighborsPerGroupid[groupId]/numOfResInGroup;
       
        Color c = _colorrs_map[_colors[groupId]][Mood::neutral]._color;
        pointsPerColor.insert({
            c,
            vector<Point>{Point((double)run, averageNumOfDiffNeighbors, c)}
        });
    }
    
    _title->print(renderer);
    _plot->print(pointsPerColor, false, renderer);
    _key->print(renderer);
}

int GrDvstyChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrDvstyChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}