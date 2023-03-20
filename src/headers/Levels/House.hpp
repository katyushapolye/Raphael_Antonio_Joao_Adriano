#include "../Core/Level.hpp"
#ifndef HOUSE_H
#define HOUSE_H
#include <iostream>

class House : public Level
{
public:
    void receiveTrigger(std::string trigger)
    {
        std::cout << "Overloaded Correctly Done" << std::endl;
    }
};

#endif
