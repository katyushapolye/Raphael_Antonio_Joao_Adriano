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

    TileDescriptor(TextureHandler::TextureAtlas iAtlas, sf::IntRect iRect, bool iWalkable, bool iTwoTileTall, std::string iTrigger = "", std::string iStoryTrigger = "", std::string iAwakeTrigger = "", sf::Vector2f iVisualOffset = sf::Vector2f(0, 0))
    {
        atlas = iAtlas;
        rect = iRect;
        isWalkable = iWalkable;
        isTwoTileTall = iTwoTileTall;
        trigger = iTrigger;
        storyTrigger = iStoryTrigger;
        awakeTrigger = iAwakeTrigger;
        visualOffset = iVisualOffset;
    };
    TextureHandler::TextureAtlas atlas;
    sf::IntRect rect;
    bool isWalkable;
    bool isTwoTileTall;
    std::string trigger = "";
    std::string storyTrigger = "";
    std::string awakeTrigger = "";

    sf::Vector2f visualOffset;
};
#endif
