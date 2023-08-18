#ifndef RESIDENT_H
#define RESIDENT_H

#include <memory>
#include <unordered_set>
#include <string>
#include "ResidentTemplate.h"

class Resident
{

protected:

    Resident (const Resident& obj) = default;
    Resident (Resident&& obj) noexcept = default;
    Resident& operator= (const Resident& obj) = default;
    Resident& operator= (Resident&& obj) noexcept = default;

public:

    // happinessGoal must be in the rage [0, 100].
    // allowedMovementDistance is how far the resident can move to inhabit a new house.
    Resident (
        int id,
        int groupId,
        double allowedMovementDistance,
        double happinessGoal);
    Resident () = delete;
    virtual ~Resident () noexcept = default;

    // Only calculates happiness. Does not set the resident's happiness.
    double calculateHappiness (
        const std::unordered_set<const Resident*>& neighbors,
        int numOfAdjacentHouses
    ) const;
    
    double getAllowedMovementDistance () const;
    int getGroupId () const;
    double getHappinessGoal () const;
    double getHappiness () const;
    int getID() const;
    
    // Returns information identifying and describing the resident, including: id, group id,
    // allowed movement, current happiness, happiness goal, and information on the resident's
    // type.
    std::string toStr () const;

    // Returns information describing the resident's type.
    std::string getType () const;

    // If this resident's id is smaller than other's id, then return true. Return false otherwise.
    bool operator< (const Resident& other) const;
    
    double setHappiness (
        const std::unordered_set<const Resident*>& neighbors,
        int numOfAdjacentHouses
    );

    virtual double getMaximumPossibleHappiness () const = 0;
    virtual double getLeastPossibleHappiness () const = 0;
    virtual std::unique_ptr<const ResidentTemplate> getTemplate () const = 0;
    
protected:

    virtual double implimentHappiness (
        const std::unordered_set<const Resident*>& neighbors,
        int numOfAdjacentHouses
    ) const = 0;

    virtual std::string implimentGetType () const = 0;

private:

    int    _id;
    int    _group_id;
    double _allowed_movement_distance;
    double _happiness_goal;
    double _curr_happiness;
};

#endif