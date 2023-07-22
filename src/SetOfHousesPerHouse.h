#ifndef SETOFHOUSESPERHOUSE_H
#define SETOFHOUSESPERHOUSE_H

#include <unordered_map>
#include <unordered_set>

#include "House.h"

typedef std::unordered_map<const House*, std::unordered_set<const House*>> sohph;

// A class that houses an unordered_map<const House*, std::unordered_set<const House*>>
class SetOfHousesPerHouse
{
public:
    void insert(const House* house, const House* houseInSet);
    bool containsKey (const House* house) const ;
    const std::unordered_set<const House*>* at (const House* house) const;
    sohph::const_iterator cbegin() const noexcept;
    sohph::const_iterator cend() const noexcept;
    sohph::const_iterator begin() const noexcept;
    sohph::const_iterator end() const noexcept;
    void reserve (int size);

    bool operator== (const SetOfHousesPerHouse& o) const;

private:
    sohph _set_of_houses_per_house{};

};

#endif