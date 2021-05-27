#ifndef CITY_GRID_H
#define CITY_GRID_H

#include "City.h"

class City_Grid: public City
{
    private:
    	std::vector<int> _addresses;
        int _width;
    
    public:
    	City_Grid (int width);
        City_Grid () = delete;
        City_Grid (const City_Grid& o) = default;
        City_Grid (City_Grid&& o) noexcept = default;
        City_Grid& operator= (const City_Grid& o) = default;
        ~City_Grid() = default;

        int getSize() const override;
        std::vector<int> getAddresses () const override;
        double dist (const int& from_address, const int& to_address) const override;
        std::vector<int> getAdjacentAdresses (int address) const override;
        int get_x (const int& address) const override;
        int get_y (const int& address) const override;
        bool equals(const City_Grid& other) const;
        virtual Coordinate getCoordinate(const int& address) const override;

};

#endif