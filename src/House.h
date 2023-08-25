#ifndef HOUSE__H
#define HOUSE__H

#include <string>

class House
{
    public:

        House (int address);
        House () = delete;
        House (const House& o) = default;
        House (House&& o) noexcept = default;
        House& operator= (const House& o) = default;
        House& operator= (House&& o) noexcept = default;
        ~House () noexcept = default;

        int getAddress () const {return _address;}
        bool operator< (const House& other) const;
        std::string toStr () const;
        

    private:
    
        int _address;
};

#endif