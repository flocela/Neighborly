#include "House.h"

House::House (int address):_address{address}{}

bool House::operator< (const House& other) const
{
    return _address < other._address;
}
