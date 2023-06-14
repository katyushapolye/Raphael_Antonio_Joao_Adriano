#include "../headers/Core/Game.hpp"
/*
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
*/

Game::Game()
{

    camera = sf::View(sf::FloatRect(0.0f, 0.0f, 640.f, 480.f));
    camera.setCenter(0, 0);
    window.create(sf::VideoMode(800, 600), "GameTest");
    camera.zoom(1.0);
    gameClock.restart();
    TextureHandler::loadAllTextures();
    loadLevel("House");
    isDialogue = false;
    isMainMenu = false;
    isPaused = false;

    defaultFont.loadFromFile("Resources/fonts/cinecaption226.ttf");

    lightShader.loadFromFile("Resources/shaders/dynamicLight.glsl", sf::Shader::Fragment);

    lightShader.setUniform("levelTexture", sf::Shader::CurrentTexture);

    // lightShader.setUniform("levelTexture2", sf::Shader::CurrentTexture);

    lightShader.setUniform("lightRadius", 100.f);
    lightShader.setUniform("defaultLight", 0.70f);
    // Debug

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

        if ((e.type == sf::Event::KeyPressed || sf::Event::KeyReleased))
        {
            if ((e.key.code == sf::Keyboard::Up ||
                 e.key.code == sf::Keyboard::Down ||
                 e.key.code == sf::Keyboard::Right ||
                 e.key.code == sf::Keyboard::Left ||
                 e.key.code == sf::Keyboard::Z) &&
                !(isDialogue || isPaused))
            {
                player->receiveInput(e);
            }
            else
            {
                DialogueHandler::receiveInput(e);
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
        if (gameClock.getElapsedTime().asSeconds() >= 0.00327777)
        {
            // MAIN GAME LOOP

            handleInput();

            // logic, the ifs depend on what logic (colision
            //  can be ignored if is a pause for example)

            // getting the final state of the grid
            if (!Game::isDialogue)
            {
                // Will only update player if dialogue is happening
                player->update();

                if ((player->getWorldPosition() == sf::Vector2i(4, 7) || player->getWorldPosition() == sf::Vector2i(5, 7)) && isHouse)
                {
                    loadLevel("City");
                }
                else if ((player->getWorldPosition() == sf::Vector2i(5, 6)) && !isHouse)
                {
                    loadLevel("House");
                }
            }

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
    lightShader.setUniform("lightPosition", player->getPosition());

    for (int i = 0; i < levelMap.size(); i++)
    {

        for (int j = 0; j < levelMap[i].size(); j++)
        {

            lightShader.setUniform("spritePosition", levelMap[i][j].getBackLayerVisual().getPosition());
            window.draw(levelMap[i][j].getBackLayerVisual(), &lightShader);
        }
    }

    for (int i = 0; i < levelMap.size(); i++)
    {

        for (int j = 0; j < levelMap[i].size(); j++)
        {

            // sf::Texture::bind(player->getSprite().getTexture());
            lightShader.setUniform("spritePosition", levelMap[i][j].getMiddleLayerVisual().getPosition());

            window.draw(levelMap[i][j].getMiddleLayerVisual(), &lightShader);
            if (player->getWorldPosition().y == i)
            {
                // we dont drawn the player with the shader, because he is always well light since he is the source of light

                lightShader.setUniform("spritePosition", player->getSprite().getPosition());
                window.draw(player->getSprite(), &lightShader);
            }
            lightShader.setUniform("spritePosition", levelMap[i][j].getFrontLayerVisual().getPosition());

            window.draw(levelMap[i][j].getFrontLayerVisual(), &lightShader);
        }
    }

    // render UI

    if (isDialogue)
    {
        // pass to dialogueHandler to generate the choices and line

        DialogueHandler::renderDialogue(window);
    }

    // debug monitor;
    renderDebugMonitor();

    window.display();
}
//

void Game::loadLevel(std::string levelName)
{
    std::string level = levelName;

    if (level == "House")
    {
        loadHouse();
    }
    else if (level == "City")
    {
        loadCity();
    }
}

void Game::loadCity(void)
{
    Game::currentLevel = new City(); // CAREFULL POINTERS

    levelHeight = 25;
    levelWidth = 25;

    if (isHouse)
    {  
        levelMap.clear();
        isHouse = false;   
    }

    for (int i = 0; i < levelHeight; i++)
    {
        levelMap.push_back(std::vector<Tile>());
        for (int j = 0; j < levelWidth; j++)
        {
            levelMap[i].push_back(Tile(sf::Vector2<int>(48 * j, 48 * i), TILE_DICTIONARY.at("snow1"))); 
        }
    }

    for (int i = 0; i < levelWidth - 2; i++)
    {

    }

    levelMap[3][4] = Tile(sf::Vector2<int>(4 * 48 ,3 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse1"));
    levelMap[3][5] = Tile(sf::Vector2<int>(5 * 48 ,3 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse2"));
    levelMap[3][6] = Tile(sf::Vector2<int>(6 * 48 ,3 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse3"));
    levelMap[4][4] = Tile(sf::Vector2<int>(4 * 48 ,4 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse4"));
    levelMap[4][5] = Tile(sf::Vector2<int>(5 * 48 ,4 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse5"));
    levelMap[4][6] = Tile(sf::Vector2<int>(6 * 48 ,4 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse6"));
    levelMap[5][4] = Tile(sf::Vector2<int>(4 * 48 ,5 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse7"));
    levelMap[5][5] = Tile(sf::Vector2<int>(5 * 48 ,5 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse8"));
    levelMap[5][6] = Tile(sf::Vector2<int>(6 * 48 ,5 * 48),TILE_DICTIONARY.at("snow1") , TILE_DICTIONARY.at("tempHouse9"));

    levelMap[8][8] = Tile(sf::Vector2<int>(8 * 48 ,8 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow1")); 
    levelMap[13][9] = Tile(sf::Vector2<int>(9 * 48 ,13 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow1")); 
    levelMap[18][16] = Tile(sf::Vector2<int>(16 * 48 ,18 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow3"));
    levelMap[13][12] = Tile(sf::Vector2<int>(12 * 48 ,13 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow3")); 
    levelMap[19][11] = Tile(sf::Vector2<int>(11 * 48 ,19 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow2")); 
    levelMap[10][2] = Tile(sf::Vector2<int>(2 * 48 ,10 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow1")); 
    levelMap[13][16] = Tile(sf::Vector2<int>(16 * 48 ,13 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow2")); 
    levelMap[14][15] = Tile(sf::Vector2<int>(15 * 48 ,14 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow1")); 
    levelMap[1][4] = Tile(sf::Vector2<int>(4 * 48 ,1 * 48),TILE_DICTIONARY.at("snow1") ,TILE_DICTIONARY.at("bushsnow2")); 

}

void Game::loadHouse(void)
{
    // will load each level along its behaviour script

    Game::currentLevel = new House(); // CAREFULL POINTERS

    levelHeight = 8; // 8
    levelWidth = 10; // 11 for good house size

    if (!isHouse)
    {  
        levelMap.clear();
        isHouse = true;   
    }

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

    for (int i = 0; i < levelWidth; i++)
    {
        levelMap[levelHeight - 1][i] = Tile(sf::Vector2<int>(48 * i, 48), TileDescriptor(false));
    }
    // HOUSE 40 40
    //(wood1)(wood1,wardrobe)(null)()()()

    levelMap[levelHeight - 1][4] = Tile(sf::Vector2<int>(48 * 4, (levelHeight - 1) * 48), TILE_DICTIONARY.at("wood1"));
    levelMap[levelHeight - 1][5] = Tile(sf::Vector2<int>(48 * 5, (levelHeight - 1) * 48), TILE_DICTIONARY.at("wood1"));

    levelMap[0][4] = Tile(sf::Vector2<int>(48 * 4, 48 * 0), TILE_DICTIONARY.at("woodwalltop1"), TILE_DICTIONARY.at("frame"));
    levelMap[0][3] = Tile(sf::Vector2<int>(48 * 3, 48 * 0), TILE_DICTIONARY.at("woodwalltop1"), TILE_DICTIONARY.at("window"));
    levelMap[0][6] = Tile(sf::Vector2<int>(48 * 6, 48 * 0), TILE_DICTIONARY.at("woodwalltop1"), TILE_DICTIONARY.at("window"));

    levelMap[1][4] = Tile(sf::Vector2<int>(48 * 4, 48 * 1), TILE_DICTIONARY.at("woodwallbotton1"), TILE_DICTIONARY.at("dresser"), TileDescriptor(), sf::Vector2f(0, +12.f));

    levelMap[4][4] = Tile(sf::Vector2<int>(48 * 4, 48 * 4), TILE_DICTIONARY.at("carpetTR"));
    levelMap[5][4] = Tile(sf::Vector2<int>(48 * 4, 48 * 5), TILE_DICTIONARY.at("carpetBR"));
    levelMap[4][5] = Tile(sf::Vector2<int>(48 * 5, 48 * 4), TILE_DICTIONARY.at("carpetTL"));
    levelMap[5][5] = Tile(sf::Vector2<int>(48 * 5, 48 * 5), TILE_DICTIONARY.at("carpetBL"));

    levelMap[1][1] = Tile(sf::Vector2<int>(48 * 1, 48 * 1), TILE_DICTIONARY.at("woodwallbotton1"), TILE_DICTIONARY.at("wardrobe"), TileDescriptor(), sf::Vector2f(0, +24.f));

    levelMap[6][9] = Tile(sf::Vector2<int>(48 * 9, 48 * 6), TILE_DICTIONARY.at("wood1"), TILE_DICTIONARY.at("bedbotton"));
    levelMap[5][9] = Tile(sf::Vector2<int>(48 * 9, 48 * 5), TILE_DICTIONARY.at("wood1"), TILE_DICTIONARY.at("bedtop"));

    levelMap[5][3] = Tile(sf::Vector2<int>(48 * 3, 48 * 5), TILE_DICTIONARY.at("wood1"), TILE_DICTIONARY.at("wardrobe"), TileDescriptor(), sf::Vector2f(0, 0));
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

void Game::renderDebugMonitor()
{

    sf::Text playerPositionX;
    sf::Text playerPositionY;
    sf::Text playerFacing;
    sf::Text playerLooking;

    playerFacing.setFont(defaultFont);
    playerPositionX.setFont(defaultFont);
    playerPositionY.setFont(defaultFont);
    playerLooking.setFont(defaultFont);

    playerFacing.setScale(0.4, 0.4);
    playerPositionX.setScale(0.5, 0.5);
    playerPositionY.setScale(0.5, 0.5);
    playerLooking.setScale(0.4, 0.4);

    playerFacing.setFillColor(sf::Color::Green);
    playerPositionX.setFillColor(sf::Color::Green);
    playerPositionY.setFillColor(sf::Color::Green);
    playerLooking.setFillColor(sf::Color::Green);

    playerPositionX.setString("X: " + std::to_string(player->getPosition().x) + " [" + std::to_string(player->getWorldPosition().x) + "]");
    playerPositionY.setString("Y: " + std::to_string(player->getPosition().y) + " [" + std::to_string(player->getWorldPosition().y) + "]");

    switch (this->player->getFacing())
    {
    case Player::Direction::North:
        playerFacing.setString("Facing: North");
        break;
    case Player::Direction::South:
        playerFacing.setString("Facing: South");
        break;
    case Player::Direction::East:
        playerFacing.setString("Facing: East");
        break;
    case Player::Direction::West:
        playerFacing.setString("Facing: West");
        break;

    default:
        break;
    }

    switch (this->player->getLooking())
    {
    case Player::Direction::North:
        playerLooking.setString("Looking: North");
        break;
    case Player::Direction::South:
        playerLooking.setString("Looking: South");
        break;
    case Player::Direction::East:
        playerLooking.setString("Looking: East");
        break;
    case Player::Direction::West:
        playerLooking.setString("Looking: West");
        break;

    default:
        break;
    }

    playerPositionY.setPosition(camera.getCenter().x - 60, camera.getCenter().y - 220);
    playerPositionX.setPosition(camera.getCenter().x - 60, camera.getCenter().y - 240);
    playerFacing.setPosition(camera.getCenter().x + 110, camera.getCenter().y - 220);
    playerLooking.setPosition(camera.getCenter().x + 110, camera.getCenter().y - 210);

    window.draw(playerPositionX);
    window.draw(playerPositionY);
    window.draw(playerFacing);
    window.draw(playerLooking);
}

void Game::startDialogueState()
{
    Game::isDialogue = true;
}

void Game::endDialogueState()
{
    Game::isDialogue = false;
}

/*

//Esboço da leitura de arquivo
void Game::LerArquivo(std::string entrada)
{
    ifstream arq;
    arq.open(entrada);
    if(!arq.is_open())
    {
        cout << "nao foi possivel abrir o arquivo." << endl;
        return;
    }
    std::string linha;

    getline(arq,linha);
    if(linha == "House")
    {
        Game::currentLevel = new House();
    }
    getline(arq,linha);

    levelHeight = atol(linha);

    getline(arq,linha);

    levelWidth = atol(linha);
    for(int i = 0 ; i<levelHeight ;i++)
    {
        stringstream ss(linha);
        string num;
        for(int j=0;j<LevelWidth;j++)
        {
            getline(ss, num,',')
            backLayer = dict[atol(num)];
            getline(ss, num,',')
            middleLayer = dict[atol(num)];
            getline(ss, num,',')
            frontLayer = dict[atol(num)];
            //levelMap[i][j] = Tile(sf::Vector2<int>(48 * 4, 48 * 4), TILE_DICTIONARY.at("carpetTR"));

        }
    }
}
*/