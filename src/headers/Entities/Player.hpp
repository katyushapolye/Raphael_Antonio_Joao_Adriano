#ifndef PLAYER_H
#define PLAYER_H
#include "../Core/TextureHandler.hpp"
#include "../Core/Game.hpp"
#include <SFML/Graphics.hpp>

class Player
{
public:
    enum class Direction;

private:
    sf::Vector2f position;
    sf::Sprite visual;

    int worldX = 0;
    int worldY = 0;

    int velocity = 100;
    // animationcontroller

    // Facing is used for position correction
    Player::Direction facing = Player::Direction::South;

    // looking is used for interaction direction and animation

    Player::Direction looking = Player::Direction::South;

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

    bool isMoving = false;

    bool interactionPending = false;

    // internal control functions

    void move();
    void correctMovement();
    void checkLevelBound();
    void checkLevelColision();

    void computeInput();

public:
    enum class Direction
    {
        North,
        South,
        East,
        West,
    };
    Player();

    void update();
    void receiveInput(sf::Event e);
    sf::Sprite &getSprite();
    sf::Vector2f getPosition();
    sf::Vector2i getWorldPosition();

    Direction getFacing();

    Direction getLooking();
};

#endif
