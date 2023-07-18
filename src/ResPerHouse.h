#ifndef RESPERHOUSE_H
#define RESPERHOUSE_H

#include <unordered_map>
#include <utility>

#include "House.h"
#include "Resident.h"

// A class that houses an unordered_map<const House*, const Resident*>
class ResPerHouse
{
public:
    void insert(std::pair<const House*, const Resident*> pair);
    bool contains (const House* house) const ;
    const Resident* at(const House* house) const;
    std::unordered_map<const House*, const Resident*>::const_iterator cbegin() const noexcept;
    std::unordered_map<const House*, const Resident*>::const_iterator cend() const noexcept;
    std::unordered_map<const House*, const Resident*>::const_iterator begin() const noexcept;
    std::unordered_map<const House*, const Resident*>::const_iterator end() const noexcept;
    void reserve (int size);

    bool operator== (const ResPerHouse& o) const;

private:
    std::unordered_map<const House*, const Resident*> _res_per_house{};

};

#endif