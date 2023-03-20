#include "../headers/Core/Game.hpp"

Game::Game()
{

    camera = sf::View(sf::FloatRect(0.0f, 0.0f, 640.f, 480.f));
    camera.setCenter(0, 0);
    camera.zoom(1.0);
    gameClock.restart();
    TextureHandler::loadAllTextures();
    loadLevel("House");
    run();
}

void Game::handleInput()
{
    sf::Event e;
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    return;
}

void Game::run()
{

    while ((window.isOpen()))
    {
        if (gameClock.getElapsedTime().asSeconds() >= 0.01666667)
        {
            // MAIN GAME LOOP

            handleInput();

            // logic, the ifs depend on what logic (colision
            //  can be ignored if is a pause for example)

            // getting the final state of the grid

            render();
        }
    }
}

void Game::render()
{
    window.clear();
    currentLevel->receiveTrigger("qualquer merda");
    sf::CircleShape s(100.0f);
    // std::cout << levelMap.empty() << std::endl;

    for (int i = 0; i < levelMap.size(); i++)
    {

        for (int j = 0; j < levelMap[i].size(); j++)
        {
            window.draw(levelMap[i][j].getBackLayerVisual());
            window.draw(levelMap[i][j].getMiddleLayerVisual());
            window.draw(levelMap[i][j].getFrontLayerVisual());
        }
    }
    window.display();
}

void Game::loadLevel(std::string levelName)
{
    // will load each level along its behaviour script

    this->currentLevel = new House();

    for (int i = 0; i < 25; i++)
    {
        levelMap.push_back(std::vector<Tile>());
        for (int j = 0; j < 25; j++)
        {
            levelMap[i].push_back(Tile(sf::Vector2<int>(48 * j, 48 * i), TILE_DICTIONARY.at("wood1"))); // TILE_DICTIONARY.at("wardrobe")));
        }
    }

    levelMap[7][7] = Tile(sf::Vector2<int>(48 * 7, 48 * 7), TILE_DICTIONARY.at("wood1"), TILE_DICTIONARY.at("wardrobe"));
}
