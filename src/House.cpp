#include "House.h"

using namespace std;

House::House (int address):_address{address}{}

bool House::operator< (const House& other) const
{
    return _address < other._address;
}

std::string House::toStr () const
{
    return "House (addr): (" + std::to_string(_address) + ")";
}

