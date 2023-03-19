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

    TileDescriptor(TextureHandler::TextureAtlas iAtlas, sf::IntRect iRect, bool iWalkable, bool iTwoTileTall, std::string iTrigger = "", std::string iStoryTrigger = "")
    {
        atlas = iAtlas;
        rect = iRect;
        isWalkable = iWalkable;
        isTwoTileTall = iTwoTileTall;
        trigger = iTrigger;
        storyTrigger = iStoryTrigger;
    };
    TextureHandler::TextureAtlas atlas;
    sf::IntRect rect;
    bool isWalkable;
    bool isTwoTileTall;
    std::string trigger = "";
    std::string storyTrigger = "";
};
