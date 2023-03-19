#include "../headers/Tile.hpp"

Tile::Tile(sf::Vector2<int> position, TileDescriptor back, TileDescriptor middle, TileDescriptor front)
{

    // The position will be set acording to the order of loading, made by the reader on the levelcontroller

    this->position = position;

    this->matrixPosition = sf::Vector2<int>(this->position.x % 48, this->position.y % 48);

    // loading visuals

    backLayer.setTexture(TextureHandler::getTexture(back.atlas));
    backLayer.setTextureRect(back.rect);
    this->backLayer.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
    if (back.trigger != "")
    {
        this->trigger = back.trigger;
    }

    if (back.isTwoTileTall)
    {
        backLayer.setScale(1.f, -1.f);
    }

    middleLayer.setTexture(TextureHandler::getTexture(middle.atlas));
    middleLayer.setTextureRect(middle.rect);
    this->middleLayer.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
    if (middle.trigger != "")
    {
        this->trigger = middle.trigger;
    }
    if (middle.isTwoTileTall)
    {
        middleLayer.setScale(1.f, -1.f);
    }

    frontLayer.setTexture(TextureHandler::getTexture(front.atlas));
    frontLayer.setTextureRect(front.rect);
    this->frontLayer.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
    if (front.trigger != "")
    {
        this->trigger = front.trigger;
    }
    if (front.isTwoTileTall)
    {
        frontLayer.setScale(1.f, -1.f);
    }

    backLayer.setPosition(this->position.x, this->position.y);
    middleLayer.setPosition(this->position.x, this->position.y);
    frontLayer.setPosition(this->position.x, this->position.y);

    this->isWalkable = back.isWalkable && middle.isWalkable && front.isWalkable;
}

sf::Sprite &Tile::getBackLayerVisual()
{
    return this->backLayer;
}

sf::Sprite &Tile::getMiddleLayerVisual()
{
    return this->middleLayer;
}
sf::Sprite &Tile::getFrontLayerVisual()
{
    return this->frontLayer;
}