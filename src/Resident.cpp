#include "Resident.h"

#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

Resident::Resident (
    int    id,
    int    groupNumber,
    double allowedMovementDistance,
    double happinessGoal
): _id{id}, 
   _group_id{groupNumber}, 
   _allowed_movement_distance{allowedMovementDistance}, 
   _happiness_goal{happinessGoal}            
{
    if (happinessGoal < 0.0 || happinessGoal > 100.0)
    {   
        throw std::invalid_argument("HappinessGoal must be between 0.0 and 100.0 inclusive.");
    }
}

int Resident::getID() const
{
    return _id;
}

int Resident::getGroupId () const
{
    return _group_id;
}

double Resident::getAllowedMovementDistance () const
{
    return _allowed_movement_distance;
}

double Resident::getHappinessGoal () const
{
    return _happiness_goal;
}

double Resident::getHappiness () const
{
    return _curr_happiness;
}

double Resident::calculateHappiness ( std::set<Resident*> neighbors, int numOfAdjacentHouses) const
{
    return implimentHappiness (neighbors, numOfAdjacentHouses);
}

double Resident::setHappiness (double happiness)
{
    _curr_happiness = happiness;
    return _curr_happiness;
}

bool Resident::operator< (const Resident& other) const // TODO upgrade this.
{
    return _id < other._id;
}

string Resident::toStrBasic () const
{
    stringstream returnStream;
    returnStream << "Resident:: id ";
    returnStream << _id;
    returnStream << " group id: ";
    returnStream << _group_id;
    returnStream << " allowed movement: ";
    returnStream << fixed << setprecision(2) << _allowed_movement_distance;
    returnStream << "current happiness / happiness goal: ";
    returnStream << fixed << setprecision(2) << _curr_happiness;
    returnStream << " /";
    returnStream << fixed << setprecision(2) << _happiness_goal;
    returnStream << implimentToStrBasic();

    return returnStream.str();
}
