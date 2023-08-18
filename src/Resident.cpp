#include <sstream>
#include <stdexcept>
#include <iomanip>

#include "Resident.h"

using namespace std;

Resident::Resident (
    int    id,
    int    groupNumber,
    double allowedMovementDistance,
    double happinessGoal
):
    _id{id}, 
    _group_id{groupNumber}, 
    _allowed_movement_distance{allowedMovementDistance}, 
    _happiness_goal{happinessGoal},
    _curr_happiness{0}         
{
    if (happinessGoal < 0.0 || happinessGoal > 100.0)
    {   
        throw std::invalid_argument("HappinessGoal must be between 0.0 and 100.0 inclusive.");
    }
}

double Resident::calculateHappiness (
    const std::unordered_set<const Resident*>& neighbors,
    int numOfAdjacentHouses
) const
{
    return implimentHappiness (neighbors, numOfAdjacentHouses);
}

double Resident::getAllowedMovementDistance () const
{
    return _allowed_movement_distance;
}

int Resident::getGroupId () const
{
    return _group_id;
}

double Resident::getHappinessGoal () const
{
    return _happiness_goal;
}

double Resident::getHappiness () const
{
    return _curr_happiness;
}

int Resident::getID() const
{
    return _id;
}

string Resident::toStr () const
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
    returnStream << implimentGetType();

    return returnStream.str();
}

string Resident::getType () const
{
    return implimentGetType();
}

bool Resident::operator< (const Resident& other) const
{
    return _id < other._id;
}

double Resident::setHappiness (
    const std::unordered_set<const Resident*>& neighbors,
    int numOfAdjacentHouses)
{
    _curr_happiness = calculateHappiness(neighbors, numOfAdjacentHouses);
    return _curr_happiness;
}