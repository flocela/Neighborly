#ifndef RESIDENT_H
#define RESIDENT_H

#include <map>
#include <set>

class Resident{
    public:
        Resident (int id,
                  int groupNumber, // resident group
                  double allowedMovementDistance,
                  double happinessGoal);
        Resident (const Resident& obj) = default;
        Resident (Resident&& obj) noexcept = default;
        Resident& operator= (const Resident& obj) = default;
        Resident& operator= (Resident&& obj) noexcept = default;
        virtual ~Resident () = default;

        virtual std::string toStrBasic () const = 0;

        int getID() const { return _ID; }
        int getGroupNumber () const { return _group_number; };
        double getAllowedMovementDistance () const { return _allowed_movement_distance; };
        double getHappinessGoal () const {
            return _happiness_goal; 
            };

        // Returns the last happiness value that was calculated. See calculateHappiness()
        double getHappiness () const  {
            return _curr_happiness;
        };

        double calculateHappiness (std::set<Resident*> neighbors, int numOfAdjacentHouses) const;

        // calculates happiness, sets resident's happiness and returns the calculated happiness
        double setHappiness (std::set<Resident*> neighbors, int numOfAdjacentHouses);
        bool operator< (const Resident& other) const;
    private:
        int    _ID;
        int    _group_number;
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