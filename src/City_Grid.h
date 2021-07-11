#ifndef CITY_GRID_H
#define CITY_GRID_H

#include "City.h"
#include <map>
#include <utility>
#include "House.h"
#include <memory>

class City_Grid: public City
{
    private:
        int _width;
        int _minX = 0;
        int _minY = 0;
        int _maxX;
        int _maxY;
    	std::vector<std::unique_ptr<House>> _houses;
        std::map<int, House*> _addrToHouseMap;
        std::map<std::pair<int, double>, std::vector<int>> _within_dist_map;
        std::set<std::pair<int, int>>::iterator selectRandom (
            const std::set<std::pair<int, int>> &s,
            size_t n
        ) const;
        std::set<House*> getEncompassedHouses (
            int minX,
            int maxX,
            int minY,
            int maxY
        ) const;
        int getAddress (int x, int y) const;
        House* selectRandom (std::set<House*>& setOfHouses) const;
    public:
    	City_Grid (int width);
        City_Grid () = delete;
        City_Grid (const City_Grid& o) = default;
        City_Grid (City_Grid&& o) noexcept = default;
        City_Grid& operator= (const City_Grid& o) = default;
        ~City_Grid () = default;

        int getSize() const override;
        std::vector<House*> getHouses () const override;
        double dist (const int& from_address, const int& to_address) const override;
        std::set<House*> getAdjacentHouses (House* house) const override;
        std::set<House*> getNearHouses (House* house, double distance) const override;
        std::set<House*> getNearHouses (
            House* house,
            double distance,
            std::set<House*> occupied,
            int count
        ) const override;
        int get_x (const int& address) const override;
        int get_y (const int& address) const override;
        bool equals(const City_Grid& other) const;
        virtual Coordinate getCoordinate(const int& address) const override;

};

#endif