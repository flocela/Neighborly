#ifndef RESIDENTTEMPLATE_H
#define RESIDENTTEMPLATE_H

#include <unordered_set>
#include <string>

// Holds basic information about a resident: the allowed movement distance, happiness goal,
// and the its type.
class ResidentTemplate {

protected:

    ResidentTemplate(const ResidentTemplate& obj) = default;
    ResidentTemplate(ResidentTemplate&& obj) noexcept = default;
    ResidentTemplate& operator= (const ResidentTemplate& obj) = default;
    ResidentTemplate& operator= (ResidentTemplate&& obj) noexcept = default;

public:

    // happinessGoal must be in the rage [0, 100].
    // happiness defaults to zero until it is set.
    // @allowedMovementDistance is how far the resident can move to inhabit a new house
    ResidentTemplate(
        double allowedMovementDistance,
        double happinessGoal);
    ResidentTemplate() = delete;
    virtual ~ResidentTemplate() noexcept = default;

    double getAllowedMovementDistance () const;
    double getHappinessGoal () const;
    virtual std::string getType () const = 0;

private:

    double _allowed_movement_distance;
    double _happiness_goal;
};

#endif