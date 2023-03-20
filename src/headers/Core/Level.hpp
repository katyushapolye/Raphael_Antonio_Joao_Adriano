#ifndef LEVEL_H
#define LEVEL_H
#include "Tile.hpp"
#include <vector>
#include <iostream>
class Level
{
protected:
    std::string name;

public:
    virtual void receiveTrigger(std::string trigger)
    {
        std::cout << "Bad Overload Done" << std::endl;
    };
};
#endif
