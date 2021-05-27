#ifndef RESIDENT_H
#define RESIDENT_H

#include <vector>
#include "Color.h"

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

        int getID() { return _ID; }
        virtual Color getColor () const { return _color; };
        virtual double getAllowedMovementDistance () const { return _allowed_movement_distance; };
        virtual double getHappinessGoal () const { return _happiness_goal; };

        // neighbors vector includes all possible neighbors, so
        // if a neighbors house is empty, Color::absent should
        // be added to neighbors
        virtual double getHappiness (std::vector<Color> neighbors) const = 0;
        
    private:
        Color  _color;
        double _allowed_movement_distance;
        double _happiness_goal;
        int    _ID;
};

#endif