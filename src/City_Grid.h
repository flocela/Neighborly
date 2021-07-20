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

        // Helper method. Returns all the houses that form a rectangular area
        // around @house. Area is 2 * @allowableDist wide and high and
        // @house is in the center of the area.
        // The set that is returned does not include @house.
        std::set<House*> getEncompassedHouses (
            House* house, 
            double allowableDist
        ) const;

        // Helper method for getSomeNearHouses. Since only have to return some
        // of the near houses instead of all of them. Randomly select houses
        // and see if they are unoccupied and if their distance is acceptable.
        // This should be faster than checking every house in an area and then
        // randomly selecting a few houses. Should be faster when a lot of the 
        // houses are unoccupied and when only a few houses need to be chosen. 
        std::set<House*> getSomeNearHousesFastAndRandom (
            House* house,
            double allowableDist,
            std::set<House*> occupied,
            int count
        ) const;

        // Helper method for getSomeNearHouses. Creates a set of all houses
        // that are within @allowableDist from @house, called nearSet. Remove all
        // occupied houses from nearSet. Then randomly choose houses from nearSet.
        std::set<House*> getSomeNearHousesSlowerAndRandom (
            House* house,
            double allowableDist,
            std::set<House*> occupied,
            int count
        ) const;
        int getAddress (int x, int y) const;
        int getMinXLine (int origX, int allowableDist) const;
        int getMaxXLine (int origX, int allowableDist) const;
        int getMinYLine (int origY, int allowableDist) const;
        int getMaxYLine (int origY, int allowableDist) const;
        House* selectRandom (std::set<House*>& setOfHouses) const;
        int selectRandom (std::set<int>& setOfInts) const;
        
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

        // Return all houses that are @allowableDist or less away from @house.
        // Returned set will not include @house.
        std::set<House*> getNearHouses (House* house, double allowableDist) const override;
        std::set<House*> getSomeNearHouses (
            House* house,
            double allowableDistance,
            std::set<House*> occupied,
            int count
        ) const override;
        int get_x (const int& address) const override;
        int get_y (const int& address) const override;
        bool equals(const City_Grid& other) const;
        virtual Coordinate getCoordinate(const int& address) const override;

};

#endif