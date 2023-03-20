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
    Tile(sf::Vector2<int> position, TileDescriptor back, TileDescriptor middle = TileDescriptor(), TileDescriptor front = TileDescriptor());

    void playerInteraction(); // will run in case of a player interaction

    sf::Sprite &getBackLayerVisual();
    sf::Sprite &getMiddleLayerVisual();
    sf::Sprite &getFrontLayerVisual();
};

// TILES DICTIONARY, HANDCRAFTED

static const inline std::unordered_map<std::string, TileDescriptor> TILE_DICTIONARY = {
    {"grass1", TileDescriptor(TextureHandler::TextureAtlas::OA2, sf::IntRect(0, 0, 48, 48), true, false)},
    {"wood1", TileDescriptor(TextureHandler::TextureAtlas::IA2, sf::IntRect(0, 144, 48, 48), true, false)},
    {"wardrobe", TileDescriptor(TextureHandler::TextureAtlas::IB0, sf::IntRect(480, 144, 49, -96), false, true, "Inspect")}, // will need invertion

};

#endif