#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "../Levels/House.hpp"
#include "TextureHandler.hpp"
#include "../Entities/Player.hpp"

class Game
{
private:
    // basic components
    sf::View camera;
    sf::Clock gameClock;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "GameTest");

    // Responsible for behaviours
    Level *currentLevel = nullptr;
    std::vector<std::vector<Tile>> levelMap;

    Player player;
    // enemies array

    // state flags
    bool isPaused = false;
    bool isMainMenu = true;
    bool isDialogue = false;

    // private funcions

    // input
    // will decide who gets the input event (UI or Player)
    void handleInput();

    // Logic Update
    void cameraUpdate();
    // player interaction will send a coordinate of the interaction to the levelcontroller

    // visual
    void render();

    // general

    void run();

    void loadLevel(std::string levelName);

public:
    Game();

    sf::View &getCamera();
};

#endif
