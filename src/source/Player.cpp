
#include "../headers/Entities/Player.hpp"
#include <cmath>

Player::Player()
{
    this->position = sf::Vector2f(48, 48); // 7 * 48);
    this->visual = sf::Sprite();
    visual.setTexture(TextureHandler::getTexture(TextureHandler::PRISCILLA));
    visual.setOrigin(24, 24);
    visual.setTextureRect(sf::IntRect(48, 96, 48, -96));
    visual.setScale(1.0f, -1.0f);
    visual.setPosition(this->position.x, this->position.y);
}

void Player::update()
{
    // debug                                                                     //small offset from center
    if (Game::getLevelMap()[round(this->position.y / 48)][1 + round((this->position.x + -25) / 48)].walkable() == false)
    {
        movingRight = false;
    }
    std::cout << "X: " << round(this->position.x / 48) << std::endl;
    std::cout << "Y: " << round(this->position.y / 48) << std::endl;
    // debug
    this->move();

    this->position = sf::Vector2f(round(this->position.x), round(this->position.y));

    this->visual.setPosition(sf::Vector2f(this->position));

    worldX = int(this->position.x) / TILE_SIZE;
    worldY = int(this->position.y) / TILE_SIZE;
    /*

    std::cout << "wX: " << worldX << "wY: " << worldY << std::endl;
    std::cout << "X: " << this->position.x << "Y: " << this->position.y << std::endl;
    std::cout << "mX: " << (int)this->position.x % 48 << "mY: " << (int)this->position.y % 48 << std::endl;

    std::cout << "Dir" << facing << std::endl;

    std::cout << "Moving Up: " << movingUp << std::endl;
    std::cout << "Moving Down: " << movingDown << std::endl;
    std::cout << "Moving Left: " << movingLeft << std::endl;
    std::cout << "Moving Right: " << movingRight << std::endl;
    */
}

sf::Sprite &Player::getSprite()
{
    return this->visual;
}

void Player::receiveInput(sf::Event e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        // 4 directional movement for ease of tile management and interaction
        if (e.key.code == sf::Keyboard::Up)
        {

            // movingDown = false;
            // movingLeft = false;
            // movingRight = false;
            movingUp = true;
            facing = North;
        }
        if (e.key.code == sf::Keyboard::Down)
        {
            // movingUp = false;
            // movingLeft = false;
            // movingRight = false;
            movingDown = true;
            facing = South;
        }
        if (e.key.code == sf::Keyboard::Left)
        {
            // movingUp = false;
            // movingDown = false;
            movingLeft = true;
            // movingRight = false;

            facing = West;
        }
        if (e.key.code == sf::Keyboard::Right)
        {
            // movingUp = false;
            // movingDown = false;
            // movingLeft = false;
            movingRight = true;
            facing = East;
        }
    }
    if (e.type == sf::Event::KeyReleased)
    {
        if (e.key.code == sf::Keyboard::Up)
        {
            movingUp = false;
        }
        if (e.key.code == sf::Keyboard::Down)
        {
            movingDown = false;
        }
        if (e.key.code == sf::Keyboard::Left)
        {
            movingLeft = false;
        }
        if (e.key.code == sf::Keyboard::Right)
        {
            movingRight = false;
        }
    }
}

void Player::move()
{
    // Illusion of tile based movement

    if (movingUp)
    {
        this->position.y -= velocity * Game::getGameClock().getElapsedTime().asSeconds();
        this->facing = North;
    }
    if (movingDown)
    {
        this->position.y += velocity * Game::getGameClock().getElapsedTime().asSeconds();
        this->facing = South;
    }
    if (movingLeft)
    {
        this->position.x -= velocity * Game::getGameClock().getElapsedTime().asSeconds();
        this->facing = West;
    }
    if (movingRight)
    {
        this->position.x += velocity * Game::getGameClock().getElapsedTime().asSeconds();
        this->facing = East;
    }
}
