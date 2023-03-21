#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "../Levels/House.hpp"
#include "TextureHandler.hpp"
#include "../Entities/Player.hpp"
// foward  declaration
class Player;

class Game
{
private:
    // basic components
    static inline sf::View camera;
    static inline sf::Clock gameClock;
    static inline sf::RenderWindow window;

    // Responsible for behaviours

    static inline std::vector<std::vector<Tile>> levelMap;
    static inline Level *currentLevel;

    Player *player;
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

    static sf::View &getCamera();
    static sf::Clock &getGameClock();
    static std::vector<std::vector<Tile>> &getLevelMap();
};

#endif
