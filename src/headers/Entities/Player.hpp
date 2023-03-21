#ifndef PLAYER_H
#define PLAYER_H
#include "../Core/TextureHandler.hpp"
#include "../Core/Game.hpp"
#include <SFML/Graphics.hpp>
class Player
{

private:
    enum Direction
    {
        North,
        South,
        East,
        West,
    };

    sf::Vector2f position;
    sf::Sprite visual;

    int worldX = 0;
    int worldY = 0;

    int velocity = 300;
    // animationcontroller

    // Facing?
    Direction facing = Player::Direction::South;
    bool movingLeft = false;
    bool movingRight = false;
    bool movingUp = false;
    bool movingDown = false;

    bool leftPressed = false;
    bool rightPressed = false;
    bool upPressed = false;
    bool downPressed = false;

    bool yCorrection = false;
    bool xCorrection = false;

    // internal control functions

    void move();
    void correctMovement();
    void checkLevelBound();
    void checkLevelColision();

    void computeInput();

public:
    Player();

    void update();
    void receiveInput(sf::Event e);
    sf::Sprite &getSprite();
    sf::Vector2f getPosition();
    sf::Vector2i getWorldPosition();
};

#endif
