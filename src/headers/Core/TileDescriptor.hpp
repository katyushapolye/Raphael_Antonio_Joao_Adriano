#ifndef TILEDESCRIPTOR_H
#define TILEDESCRIPTOR_H
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextureHandler.hpp"
struct TileDescriptor
{
    TileDescriptor()
    {
        isWalkable = true;
    };
    TileDescriptor(bool isWalkable)
    {
        this->isWalkable = isWalkable;
    };

    TileDescriptor(TextureHandler::TextureAtlas iAtlas, sf::IntRect iRect, bool iWalkable, bool iTwoTileTall, std::string iTrigger = "", sf::Vector2f iVisualOffset = sf::Vector2f(0, 0))
    {
        atlas = iAtlas;
        rect = iRect;
        isWalkable = iWalkable;
        isTwoTileTall = iTwoTileTall;
        trigger = iTrigger;
        visualOffset = iVisualOffset;
    };
    TextureHandler::TextureAtlas atlas;
    sf::IntRect rect;
    bool isWalkable;
    bool isTwoTileTall;
    std::string trigger = "";

    sf::Vector2f visualOffset;
};
#endif
