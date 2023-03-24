#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "TileDescriptor.hpp"
#include "TextureHandler.hpp"
#define TILE_SIZE 48
class Tile // we may inherit other more specifics tiles from this class
{
private:
    // visuals
    sf::Sprite backLayer;
    sf::Sprite middleLayer;
    sf::Sprite frontLayer;

    // Position

    sf::Vector2<int> position;

    sf::Vector2<int> matrixPosition;

    // control

    // even with 3 layers on the tile, the last layer (front) trigger will take priority, simplification
    std::string storyTrigger = "";
    std::string trigger = "";
    std::string awakeTrigger = "";

    bool isWalkable = true; // will be an AND between all layers walkable state

    void sendTrigger(); // sends trigger to levelController/GameControler for story events or key interactions
    void sendStoryTrigger();
    void sendAwakeTrigger();

public:
    Tile(sf::Vector2<int> position, TileDescriptor back, TileDescriptor middle = TileDescriptor(), TileDescriptor front = TileDescriptor(), sf::Vector2f visualLayerOffset = sf::Vector2f(0, 0));

    void playerInteraction(); // will run in case of a player interaction

    sf::Sprite &getBackLayerVisual();
    sf::Sprite &getMiddleLayerVisual();
    sf::Sprite &getFrontLayerVisual();

    std::string getTrigger();

    bool walkable();
};

// TILES DICTIONARY, HANDCRAFTED

static const inline std::unordered_map<std::string, TileDescriptor> TILE_DICTIONARY = {
    // Multi tiles horizontal blocks can work if they are on a wall or are not collideble
    {"grass1", TileDescriptor(TextureHandler::TextureAtlas::OA2, sf::IntRect(0, 0, 48, 48), true, false)},
    {"wood1", TileDescriptor(TextureHandler::TextureAtlas::IA2, sf::IntRect(0, 48 * 8, 48, 48), true, false)},
    {"woodwallbotton1", TileDescriptor(TextureHandler::TextureAtlas::IA4, sf::IntRect(48, 9 * 48, 48, 48), false, false)},
    {"woodwalltop1", TileDescriptor(TextureHandler::TextureAtlas::IA4, sf::IntRect(48, 8 * 48, 48, 48), false, false)},
    {"carpetTR", TileDescriptor(TextureHandler::IA2, sf::IntRect(48 * 4, 48 * 10, 48, 48), true, false)},
    {"carpetBR", TileDescriptor(TextureHandler::IA2, sf::IntRect(48 * 4, 48 * 11, 48, 48), true, false)},
    {"carpetTL", TileDescriptor(TextureHandler::IA2, sf::IntRect(48 * 5, 48 * 10, 48, 48), true, false)},
    {"carpetBL", TileDescriptor(TextureHandler::IA2, sf::IntRect(48 * 5, 48 * 11, 48, 48), true, false)},

    {"dresser", TileDescriptor(TextureHandler::IB0, sf::IntRect(8 * 48, 2 * 48, 96, 48), false, false)},

    {"bedbotton", TileDescriptor(TextureHandler::IB0, sf::IntRect(8 * 48, 6 * 48, 48, 48), false, false)},
    {"bedtop", TileDescriptor(TextureHandler::IB0, sf::IntRect(8 * 48, 5 * 48, 48, 48), false, false)},

    {"frame", TileDescriptor(TextureHandler::TextureAtlas::IB0, sf::IntRect(480, 0, 96, 48), false, false)}, // need to look into
    {"cupboard", TileDescriptor(TextureHandler::IB0, sf::IntRect(432, 96, 48, 48), false, false)},
    {"window", TileDescriptor(TextureHandler::IB0, sf::IntRect(5 * 48, 400, 48, 60), false, false)},
    {"wardrobe", TileDescriptor(TextureHandler::TextureAtlas::IB0, sf::IntRect(480, 144, 48, -96), false, true)}, // will need invertion

};

#endif