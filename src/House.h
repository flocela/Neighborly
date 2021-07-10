#ifndef HOUSE_H
#define HOUSE_H

class House
{
    public:

        House (int address);
        House () = delete; // Can't make this delete because then can't make an empty vector.
        House (const House& o) = default;
        House (House&& o) noexcept = default;
        House& operator= (const House& o) = default;
        ~House () = default;

        int _address;
        bool operator< (const House& other) const;
};

#endif