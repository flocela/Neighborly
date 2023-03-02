#ifndef RESIDENT_H
#define RESIDENT_H

#include <set>
#include <string>

class Resident{

public:
    Resident (
        int id,
        int groupId,
        double allowedMovementDistance,
        double happinessGoal);
    Resident () = delete;
    Resident (const Resident& obj) = default;
    Resident (Resident&& obj) noexcept = default;
    Resident& operator= (const Resident& obj) = default;
    Resident& operator= (Resident&& obj) noexcept = default;
    virtual ~Resident () = default; //TODO should be virtual

    std::string toStrBasic () const;

    int getID() const;
    int getGroupId () const;
    double getAllowedMovementDistance () const;
    double getHappinessGoal () const;
    double getHappiness () const;
    bool operator< (const Resident& other) const;
    double calculateHappiness (std::set<Resident*> neighbors, int numOfAdjacentHouses) const; // TODO should be const Resident*

    double setHappiness (double happiness);
    
protected:
    virtual double implimentHappiness (
        std::set<Resident*> neighbors,
        int numOfAdjacentHouses
    ) const = 0;

    virtual std::string implimentToStrBasic () const = 0;

private:
    int    _id;
    int    _group_id;
    double _allowed_movement_distance;
    double _happiness_goal;
    double _curr_happiness;
};

#endif