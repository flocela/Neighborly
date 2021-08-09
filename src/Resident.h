#ifndef RESIDENT_H
#define RESIDENT_H

#include <vector>
#include "Color.h"
#include "City.h"
#include <map>
#include <set>

class Resident{
    public:
        Resident (int id,
                  Color color, 
                  double allowedMovementDistance,
                  double happinessGoal);
        Resident (const Resident& obj) = default;
        Resident (Resident&& obj) noexcept = default;
        Resident& operator= (const Resident& obj) = default;
        Resident& operator= (Resident&& obj) noexcept = default;
        virtual ~Resident () = default;

        virtual std::string toStrBasic () const = 0;

        int getID() const { return _ID; }
        virtual Color getColor () const { return _color; };
        virtual double getAllowedMovementDistance () const { return _allowed_movement_distance; };
        virtual double getHappinessGoal () const { return _happiness_goal; };
        virtual double getHappiness () const {return _curr_happiness;};
        // neighbors vector includes all possible neighbors, so
        // if a neighbors house is empty, Color::absent should
        // be added to neighbors
        double calculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        );
        virtual House* findHome (
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesToNeighbors,
            std::map<House*, Resident*> houseToResMap // This should be const. Or only send a copy of needed neighbors
        ) const = 0;
        virtual House* findBestHome (
            House* oldHouse,
            std::map<House*, std::set<House*>> openHousesToNeighbors,
            std::map<House*, Resident*> houseToResMap// This should be const. Or only send a copy of needed neighbors
        ) const = 0;
        
    private:
        int    _ID;
        Color  _color;
        double _allowed_movement_distance;
        double _happiness_goal;
        double _curr_happiness;

    protected:
        virtual double implCalculateHappiness (
            std::set<Resident*> neighbors,
            int numOfAdjacentHouses
        ) const = 0;
       
};

#endif