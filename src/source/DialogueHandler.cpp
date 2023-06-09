#include "../headers/Components/DialogueHandler.hpp"

void DialogueHandler::startDialogue(std::string dialogueName)
{
    std::cout << "Starting Dialogue Bootstrap" << std::endl;
    // resseting all vars
    lineNumber = 0;
    labelMap.clear();

    // mapping the labels to lines

    std::ifstream file;

    Game::startDialogueState();
    std::string dir = "Resources/dialogues/" + dialogueName;
    file.open(dir);
    std::string line;
    std::string buffer;
    int i = 0;
    if (file.is_open())
    {

        while (getline(file, line))
        {
            lines.push_back(line);

            // Checking the command
            if (line[0] == '#')
            {
                // push the label in the map with adress line + 1

                while (line[i] != ';')
                {
                    buffer += line[i];
                    i++;
                }
                i = 0;
                labelMap.insert(std::pair<std::string, int>(buffer, (lineNumber + 1)));
                buffer = "";
            }

            DialogueHandler::lineNumber++;
        }

        // starting UI

        DialogueHandler::backPanel.setTexture(TextureHandler::getTexture(TextureHandler::WINDOW));
        DialogueHandler::backPanel.setTextureRect(sf::IntRect(0, 0, 96, 96));
        backPanel.setScale(3, 1.25);
        backPanel.setPosition(Game::getCamera().getCenter().x - 145, Game::getCamera().getCenter().y + 100);

        dialogueLineText.setFont(Game::defaultFont);
        dialogueNameText.setFont(Game::defaultFont);

        dialogueNameText.setCharacterSize(16);
        dialogueNameText.setPosition(Game::getCamera().getCenter().x - 135, Game::getCamera().getCenter().y + 100);

        dialogueLineText.setCharacterSize(15);
        dialogueLineText.setPosition(Game::getCamera().getCenter().x - 115, Game::getCamera().getCenter().y + 130);
        buttonTimeout.restart();
    }
    lineNumber = 0;

    for (auto label = labelMap.begin(); label != labelMap.end(); label++)
    {
        std::cout << label->first << ": " << label->second << std::endl;
    }
}

void DialogueHandler::receiveInput(sf::Event e)
{
    // timeout for pressing key
    if (buttonTimeout.getElapsedTime().asSeconds() < 1.5)
    {
        return;
    }
    if (e.key.code == sf::Keyboard::Z)
    {
        nextLine();
        buttonTimeout.restart();
    }
}

void DialogueHandler::nextLine()
{
    lineNumber = nextLineNumber;
    nextLineNumber = 0;
}

void DialogueHandler::renderDialogue(sf::RenderWindow &window)
{
    window.draw(DialogueHandler::backPanel);
    std::string dialogueLine = parseLine(); // stick animation into this function if any

    window.draw(dialogueLineText);
    window.draw(dialogueNameText);

    std::cout << lines[lineNumber] << std::endl;
}

std::string DialogueHandler::parseLine()
{
    std::string buffer = lines[lineNumber];

    std::string NPCname = "";
    std::string dialogueLine = "";

    int i = 2;

    while (buffer[i] != '$')
    {
        NPCname += buffer[i];
        i++;
    }
    std::cout << NPCname << std::endl;

    if (buffer[0] == 'J')
    {
        isJump = true;

        // alter the next line adress
    }
    if (buffer[0] == 'C')
    {
        isChoice = true;
        //
    }
    if (buffer[0] == 'L')
    {
        isJump = false;
        isChoice = false;

        i += 2;

        int textWidth = 0; // control for wraping

        while (buffer[i] != '"')
        {
            dialogueLine += buffer[i];
            i++;
            textWidth++;
            if (textWidth == 30)
            {

                dialogueLine += '\n';
                textWidth = 0;
            }
        }
        std::cout << dialogueLine << std::endl;

        // Setting UI

        dialogueLineText.setString(dialogueLine);
        dialogueNameText.setString(NPCname);

        // Setting next line

        nextLineNumber = lineNumber + 1;
    }
}
