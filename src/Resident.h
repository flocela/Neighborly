#ifndef RESIDENT_H
#define RESIDENT_H

#include <set>
#include <string>

class Resident{

protected:
    Resident (const Resident& obj) = default;
    Resident (Resident&& obj) noexcept = default;
    Resident& operator= (const Resident& obj) = default;
    Resident& operator= (Resident&& obj) noexcept = default;

public:
    Resident (
        int id,
        int groupId,
        double allowedMovementDistance,
        double happinessGoal);
    Resident () = delete;
    virtual ~Resident () = default;

    double calculateHappiness (std::set<const Resident*> neighbors, int numOfAdjacentHouses) const;
    double getAllowedMovementDistance () const;
    int getGroupId () const;
    double getHappinessGoal () const;
    double getHappiness () const;
    int getID() const;
    std::string toStr () const;
    std::string toStrType () const;

    bool operator< (const Resident& other) const;
    
    double setHappiness (double happiness);
    
protected:
    virtual double implimentHappiness (
        std::set<const Resident*> neighbors,
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