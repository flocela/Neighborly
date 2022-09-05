#include "TextHelper.h"
#include <sstream>
#include <algorithm>
#include <iomanip>

bool pComp(const House* a, const House* b) {return *a < *b; }

std::string TextHelper::createText (
    std::map<const House*, Resident*> residentPerHouse,
    int run
    ) const
{
    (void) residentPerHouse;
    for (const House* h : _city_ptr->getHouses())
    {
        _city_ptr->getCoordinate(h->getAddress());
    }
    std::ostringstream s1;
    s1 << "Run/FinalRun: " << run;
    s1 << " / " << _max_num_of_runs << "\n";
    s1 << "Resident presented as:\n";
    s1 << "Resident ID, color, address, coordinate, happiness / happiness goal \n";
    
    std::set<int> seenColors;
    std::set<Resident*> seenResidents;
    std::vector<const House*> housesInOrder;
    for (auto h2r : residentPerHouse)
    {   
        const House* house = h2r.first;
        Resident* res = h2r.second;
        housesInOrder.push_back(house);
        if (seenColors.count(res->getGroupNumber()) == 0)
        {
            seenResidents.insert(res);
            seenColors.insert(res->getGroupNumber());
        }
    }
    std::sort(housesInOrder.begin(), housesInOrder.end(), pComp);
    for (const House* house : housesInOrder)
    {
        Resident* res = residentPerHouse[house];
        s1 << std::setw(3) << res->getID() << ", ";
        s1 << std::setw(5) << res->getGroupNumber() << ", ";
        s1 << std::setw(2) << house->getAddress() << ", ";
        s1 << std::setw(8) << _city_ptr->getCoordinate(house->getAddress()).toStr() << ", ";
        s1 << res->getHappiness() << "/";
        s1 << res->getHappinessGoal() << "\n";
    }
    return s1.str();
}