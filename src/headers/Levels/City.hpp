#include "../Core/Level.hpp"
#ifndef CITY_H
#define CITY_H
#include <iostream>

class City : public Level
{
public:
    void receiveTrigger(std::string trigger)
    {
        std::cout << "Overloaded Correctly Done" << std::endl;
    }
};

#endif