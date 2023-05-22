#ifndef HAPPINESSFUNCTION_H
#define HAPPINESSFUNCTION_H

// HappinessFunc has an x-axis of Diversity and a y-axis of Happiness.
// Both axes range from 0.0 to 1.0.
class HappinessFunc
{
protected:
    HappinessFunc () = default;
    HappinessFunc (const HappinessFunc& o) = default;
    HappinessFunc (HappinessFunc&& o) noexcept = default;
    HappinessFunc& operator= (const HappinessFunc& o) = default;
    HappinessFunc& operator= (HappinessFunc&& o) noexcept = default;

public:
    virtual ~HappinessFunc () = default;

    virtual double calcHappiness (
        int tot_num_of_possible_neighbors, 
        int num_of_like_neighbors, 
        int num_of_diff_neighbors) const = 0;
    
    virtual std::string toStrBasic () const = 0;

    virtual double getLargestValue () const = 0;
    virtual double getSmallestValue () const = 0;

};

#endif