#include <SFML/Graphics.hpp>
#include "../headers/TextureHandler.hpp"
#include <filesystem>
#include <iostream>
#include "../headers/Tile.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    std::cout << std::filesystem::current_path() << std::endl;

    TextureHandler::loadAllTextures();

    std::vector<std::vector<Tile>> test;
    for (int i = 0; i < 25; i++)
    {
        test.push_back(std::vector<Tile>());
        for (int j = 0; j < 25; j++)
        {
            test[i].push_back(Tile(sf::Vector2<int>(48 * j, 48 * i), TILE_DICTIONARY.at("wood1"))); // TILE_DICTIONARY.at("wardrobe")));
        }
    }
    test[8][8] = Tile(sf::Vector2<int>(8 * 48, 8 * 48), TILE_DICTIONARY.at("wood1"), TILE_DICTIONARY.at("wardrobe"));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 25; j++)
            {

                window.draw(test[i][j].getBackLayerVisual());
                window.draw(test[i][j].getMiddleLayerVisual());
                window.draw(test[i][j].getFrontLayerVisual());
            }
        }
        window.display();
    }

    return 0;
}