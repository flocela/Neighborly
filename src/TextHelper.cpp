#include "TextHelper.h"

std::string TextHelper::createText (
    std::map<House*, Resident*> residentPerHouse,
    int run,
    std::string title
    ) const
{
    (void) title;
    std::string text = "Run/FinalRun: " + run;
    text.append("/"); 
    text.append(_max_num_of_runs + "\n");

    text.append("Resident presented as: \n");
    text.append("Resident ID, color, address, coordinate,"
        " happiness / happiness goal \n");

    std::set<Color> seenColors;
    std::set<Resident*> seenResidents;
    for (auto h2r : residentPerHouse)
    { 
        House* house = h2r.first;
        Resident* res = h2r.second;
        if (seenColors.count(res->getColor()) == 0)
        {
            seenResidents.insert(res);
            seenColors.insert(res->getColor());
        }
        text.append(std::to_string(res->getID())).append(", ");
        text.append(colorMap[res->getColor()]).append(", ");
        text.append(std::to_string(house->_address)).append(", ");
        text.append(_city_ptr->getCoordinate(house->_address).toStr()).append(", ");
        text.append(std::to_string(res->getHappiness())).append("/");
        text.append(std::to_string(res->getHappinessGoal())).append("\n");
    }
    return text;
}