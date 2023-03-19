#ifndef LEVELCONTROLLER_H
#define LEVELCONTROLLER_h

#include <iostream>
#include "Level.hpp"

class LevelController
{
private:
    /* data */
public:
    LevelController(/* args */);
    Level loadLevel(std::string levelName);
};
#endif
