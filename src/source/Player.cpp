
#include "../headers/Entities/Player.hpp"
#include <cmath>

Player::Player()
{
    this->position = sf::Vector2f(48 * 2, 48 * 2); // 7 * 48);
    this->visual = sf::Sprite();
    visual.setTexture(TextureHandler::getTexture(TextureHandler::PRISCILLA));
    visual.setOrigin(24, 24);
    visual.setTextureRect(sf::IntRect(48, 96, 48, -96));
    visual.setScale(1.0f, -1.0f);
    visual.setPosition(this->position.x, this->position.y);
}

void Player::update()
{
    // debug
    computeInput();

    this->checkLevelBound();
    this->checkLevelColision();

    this->move();

    this->position = sf::Vector2f(round(this->position.x), round(this->position.y));

    this->visual.setPosition(sf::Vector2f(this->position));

    worldX = int(this->position.x) / TILE_SIZE;
    worldY = int(this->position.y) / TILE_SIZE;
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
            upPressed = true;
        }
        if (e.key.code == sf::Keyboard::Down)
        {
            // movingUp = false;
            // movingLeft = false;
            // movingRight = false;
            downPressed = true;
        }
        if (e.key.code == sf::Keyboard::Left)
        {
            // movingUp = false;
            // movingDown = false;
            leftPressed = true;
            // movingRight = false;
        }
        if (e.key.code == sf::Keyboard::Right)
        {
            // movingUp = false;
            // movingDown = false;
            // movingLeft = false;
            rightPressed = true;
        }
    }
    if (e.type == sf::Event::KeyReleased)
    {
        if (e.key.code == sf::Keyboard::Up)
        {
            upPressed = false;
        }
        if (e.key.code == sf::Keyboard::Down)
        {
            downPressed = false;
        }
        if (e.key.code == sf::Keyboard::Left)
        {
            leftPressed = false;
        }
        if (e.key.code == sf::Keyboard::Right)
        {
            rightPressed = false;
        }
    }
}

void Player::move()
{
    // Illusion of tile based movement
    // make movement dependent on both the keypressed AND the hability to move (movingDir)

    if ((int)this->position.x % TILE_SIZE != 0 && this->facing == East)
    {
        // std::cout << "Triggering Corrections" << std::endl;
        this->position.x++;
        this->facing = East;
        return;
    }

    if ((int)this->position.x % TILE_SIZE != 0 && this->facing == West)
    {
        // std::cout << "Triggering Corrections" << std::endl;
        this->position.x--;
        this->facing = West;
        return;
    }

    if ((int)this->position.y % TILE_SIZE != 0 && this->facing == North)
    {
        this->position.y--;
        this->facing = North;
        return;
    }
    if ((int)this->position.y % TILE_SIZE != 0 && this->facing == South)
    {
        this->position.y++;
        this->facing = South;
        return;
    }

    if (this->movingUp == true)
    {
        this->position.y--;
        this->facing = North;
        return;
    }
    if (this->movingDown == true)
    {
        this->position.y++;
        this->facing = South;
        return;
    }
    if (this->movingLeft == true)
    {
        this->position.x--;
        this->facing = West;
        return;
    }
    if (this->movingRight == true)
    {
        this->position.x++;
        this->facing = East;
        return;
    }

    // correction
}

sf::Vector2f Player::getPosition()
{
    return this->position;
}

void Player::checkLevelBound()
{
    // x
    if (this->position.x <= 0)
    {
        this->movingLeft = false;
        this->position.x = 0;
    }
    else if (this->position.x >= (Game::getLevelWidth() - 1) * TILE_SIZE)
    {
        this->movingRight = false;
        this->position.x = (Game::getLevelWidth() - 1) * TILE_SIZE;
    }

    // y
    if (this->position.y <= 0)
    {
        this->movingUp = false;
        this->position.y = 0;
    }

    else if (this->position.y >= (Game::getLevelHeight() - 1) * TILE_SIZE)
    {
        this->movingDown = false;
        this->position.y = (Game::getLevelHeight() - 1) * TILE_SIZE;
    }
}
sf::Vector2i Player::getWorldPosition()
{
    return sf::Vector2i(this->worldX, this->worldY);
}

void Player::checkLevelColision()
{
    // x axis
    if (Game::getLevelMap()[round(this->position.y / TILE_SIZE)][1 + round((this->position.x) / TILE_SIZE)].walkable() == false)
    {
        movingRight = false;
    }
    if (Game::getLevelMap()[round(this->position.y / TILE_SIZE)][(round((this->position.x) / TILE_SIZE) - 1)].walkable() == false)
    {
        movingLeft = false;
    }

    // special check for out of bounds on map
    if ((round((this->position.y) / TILE_SIZE) - 1) < 0)
    {
        movingUp = false;
        return;
    }
    if (1 + round((this->position.y) / TILE_SIZE) >= Game::getLevelHeight())
    {
        movingDown = false;
        return;
    }

    if (Game::getLevelMap()[1 + round((this->position.y) / TILE_SIZE)][round(this->position.x / TILE_SIZE)].walkable() == false)
    {
        movingDown = false;
    }
    if (Game::getLevelMap()[(round((this->position.y) / TILE_SIZE) - 1)][round(this->position.x / TILE_SIZE)].walkable() == false)
    {
        movingUp = false;
    }

    // y axis
}

void Player::computeInput()
{
    this->movingDown = downPressed;
    this->movingUp = upPressed;
    this->movingLeft = leftPressed;
    this->movingRight = rightPressed;
}
