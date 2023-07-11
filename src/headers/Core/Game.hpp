#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "../Levels/House.hpp"
#include "../Levels/City.hpp"
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

    static inline int levelHeight = 0;
    static inline int levelWidth = 0;

    Player *player;
    // enemies array

    // state flags
    static inline bool isPaused = false;
    static inline bool isMainMenu = false;
    static inline bool isDialogue = false;

    static inline bool isHouse = true;
    static inline bool isCity = false;

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

    void loadHouse();
    void loadCity();
    void loadForest();

    // void LerArquivo(std::string arquivo);

    // debug things

    void renderDebugMonitor();
    sf::Shader darkShader;
    sf::Shader lightShader;

public:
    static inline sf::Font defaultFont;

    Game();

    static sf::View &getCamera();
    static sf::Clock &getGameClock();
    static std::vector<std::vector<Tile>> &getLevelMap();
    static int getLevelHeight();
    static int getLevelWidth();

    static void startDialogueState();
    static void endDialogueState();
};

#endif
