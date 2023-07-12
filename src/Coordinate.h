#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

class Coordinate
{
public:
    Coordinate(int x, int y);
    Coordinate() = delete;
    Coordinate (const Coordinate& obj) = default;
    Coordinate (Coordinate&& obj) noexcept = default;
    Coordinate& operator=(const Coordinate& obj) = default;
    Coordinate& operator=(Coordinate&& obj) noexcept = default;
    ~Coordinate () noexcept = default;

    int getX() const { return _x; };
    int getY() const { return _y; };
    bool operator<(const Coordinate& a) const;
    std::string toStr() const;
    
    friend std::ostream& operator<<(std::ostream& os, Coordinate const& c);
    bool operator==(const Coordinate& c) const;
    bool operator!=(const Coordinate& c) const;

private:
    int _x = -1;
    int _y = -1;

};

namespace std
{
    template<>
    struct hash<Coordinate>
    {
        size_t operator()(const Coordinate& o) const
        {
            return ((hash<float>()(o.getX())^(hash<float>()(o.getY())<<1))>>1);
        }
    };
}

#endif