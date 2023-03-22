#include "../headers/Core/Game.hpp"

Game::Game()
{

    camera = sf::View(sf::FloatRect(0.0f, 0.0f, 640.f, 480.f));
    camera.setCenter(0, 0);
    window.create(sf::VideoMode(800, 600), "GameTest");
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

        if (e.type == sf::Event::KeyPressed || sf::Event::KeyReleased)
        {
            if ((e.key.code == sf::Keyboard::Up ||
                 e.key.code == sf::Keyboard::Down ||
                 e.key.code == sf::Keyboard::Right ||
                 e.key.code == sf::Keyboard::Left) &&
                !(isDialogue || isPaused))
            {
                player->receiveInput(e);
            }
        }
    }

    return;
}

void Game::cameraUpdate()
{
    // follow player

    camera.setCenter(player->getPosition());

    // case for edge of screen
    // camera is 800x600 too
    if (camera.getCenter().x - 300 <= -TILE_SIZE)
    {
        camera.setCenter(300 - TILE_SIZE, camera.getCenter().y);
    }
    if (camera.getCenter().x + 300 >= (Game::getLevelWidth()) * TILE_SIZE)
    {
        camera.setCenter((Game::getLevelWidth()) * TILE_SIZE - 300, camera.getCenter().y);
    }

    /* NEED TO DO FOR THE Y AXIS
    if (camera.getCenter().y - 400 >= TILE_SIZE * Game::getLevelHeight())
    {
        camera.setCenter(camera.getCenter().x, TILE_SIZE * Game::getLevelHeight() - 400);
    }*/

    // case for level being smaller than the screen
    // cannot return and must check all in case of vertical/horizontal long level

    if (levelHeight < 9)
    {
        camera.setCenter(camera.getCenter().x, (int)((levelHeight - 1) * TILE_SIZE) / 2);
    }
    if (levelWidth < 12)
    {
        camera.setCenter((int)((levelWidth - 1) * TILE_SIZE) / 2, this->camera.getCenter().y);
    }
}

void Game::run()
{
    player = new Player();

    while ((window.isOpen()))
    {
        if (gameClock.getElapsedTime().asSeconds() >= 0.0033)
        {
            // MAIN GAME LOOP

            handleInput();

            // logic, the ifs depend on what logic (colision
            //  can be ignored if is a pause for example)

            // getting the final state of the grid
            player->update();

            cameraUpdate();

            render();

            gameClock.restart();
        }
    }
}

void Game::render()
{
    window.clear();

    window.setView(camera);
    // std::cout << levelMap.empty() << std::endl;

    for (int i = 0; i < levelMap.size(); i++)
    {

        for (int j = 0; j < levelMap[i].size(); j++)
        {
            window.draw(levelMap[i][j].getBackLayerVisual());
        }
    }

    for (int i = 0; i < levelMap.size(); i++)
    {

        for (int j = 0; j < levelMap[i].size(); j++)
        {

            window.draw(levelMap[i][j].getMiddleLayerVisual());
            if (player->getWorldPosition().y == i)
            {
                window.draw(player->getSprite());
            }
            window.draw(levelMap[i][j].getFrontLayerVisual());
        }
    }

    // debug monitor;

    window.display();
}
//

void Game::loadLevel(std::string levelName)
{
    // will load each level along its behaviour script

    Game::currentLevel = new House(); // CAREFULL POINTERS

    levelHeight = 8; // 8
    levelWidth = 11; // 11 for good house size

    for (int i = 0; i < levelHeight; i++)
    {
        levelMap.push_back(std::vector<Tile>());
        for (int j = 0; j < levelWidth; j++)
        {
            levelMap[i].push_back(Tile(sf::Vector2<int>(48 * j, 48 * i), TILE_DICTIONARY.at("wood1"))); // TILE_DICTIONARY.at("wardrobe")));
        }
    }
    for (int i = 0; i < levelWidth; i++)
    {
        levelMap[1][i] = Tile(sf::Vector2<int>(48 * i, 48), TILE_DICTIONARY.at("woodwallbotton1"));

        levelMap[0][i] = Tile(sf::Vector2<int>(48 * i, 0), TILE_DICTIONARY.at("woodwalltop1"));
    }

    levelMap[0][4] = Tile(sf::Vector2<int>(48 * 4, 48 * 0), TILE_DICTIONARY.at("woodwalltop1"), TILE_DICTIONARY.at("frame"));
    levelMap[0][3] = Tile(sf::Vector2<int>(48 * 3, 48 * 0), TILE_DICTIONARY.at("woodwalltop1"), TILE_DICTIONARY.at("window"));
    levelMap[0][6] = Tile(sf::Vector2<int>(48 * 6, 48 * 0), TILE_DICTIONARY.at("woodwalltop1"), TILE_DICTIONARY.at("window"));

    levelMap[1][1] = Tile(sf::Vector2<int>(48 * 1, 48 * 1), TILE_DICTIONARY.at("woodwallbotton1"), TILE_DICTIONARY.at("wardrobe"), TileDescriptor(), sf::Vector2f(0, +20.f));
}

sf::View &Game::getCamera()
{
    return camera;
}
sf::Clock &Game::getGameClock()
{
    return gameClock;
}

std::vector<std::vector<Tile>> &Game::getLevelMap()
{
    return levelMap;
}

int Game::getLevelHeight()
{
    return levelHeight;
}
int Game::getLevelWidth()
{
    return levelWidth;
}