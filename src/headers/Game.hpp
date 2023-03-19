#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

#include "headers/Level.hpp"
#include "headers/LevelController.hpp"

class Game
{
private:
    // basic components
    sf::View camera;
    Level currentLevel;
    LevelController levelController;

    // state flags
    bool isPaused;

public:
    Game();

    void start();
};

#endif
