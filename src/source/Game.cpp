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

void Game::run()
{
    player = new Player();

    while ((window.isOpen()))
    {
        if (gameClock.getElapsedTime().asSeconds() >= 0.00167777)
        {
            // MAIN GAME LOOP

            handleInput();

            // logic, the ifs depend on what logic (colision
            //  can be ignored if is a pause for example)

            // getting the final state of the grid
            player->update();

            render();

            gameClock.restart();
        }
    }
}

void Game::render()
{
    window.clear();

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
    //
    window.draw(player->getSprite());

    window.display();
}

void Game::loadLevel(std::string levelName)
{
    // will load each level along its behaviour script

    Game::currentLevel = new House(); // CAREFULL POINTERS

    for (int i = 0; i < 5; i++)
    {
        levelMap.push_back(std::vector<Tile>());
        for (int j = 0; j < 5; j++)
        {
            levelMap[i].push_back(Tile(sf::Vector2<int>(48 * j, 48 * i), TILE_DICTIONARY.at("wood1"))); // TILE_DICTIONARY.at("wardrobe")));
        }
    }

    levelMap[2][2] = Tile(sf::Vector2<int>(48 * 2, 48 * 2), TILE_DICTIONARY.at("wood1"), TILE_DICTIONARY.at("wardrobe"));

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            std::cout << " " << levelMap[i][j].walkable();
        }
        std::cout << std::endl;
    }
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