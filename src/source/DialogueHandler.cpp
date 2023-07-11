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
    int i = 1;
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
                i = 1;
                labelMap.insert(std::pair<std::string, int>(buffer, (lineNumber + 1)));
                buffer = "";
            }

            DialogueHandler::lineNumber++;
        }

        // std::cout << "Lines Read" << std::endl;
        for (int i = 0; i < lines.size(); i++)
        {
            // std::cout << i << "-" << lines[i] << std::endl;
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
        // std::cout << label->first << ": " << label->second << std::endl;
    }
}

void DialogueHandler::endDialogue()
{

    Game::endDialogueState();
    lineNumber = 0;
    labelMap.clear();
    lines.clear();
    buttonTimeout.restart();
    isChoice = false;
    isParsed = false;
    choiceMap.clear();
    nextLineNumber = 1;
    dialogueLineText.setString("");
    dialogueNameText.setString("");
}

void DialogueHandler::receiveInput(sf::Event e)
{
    // timeout for pressing key
    if (buttonTimeout.getElapsedTime().asSeconds() < 1.5)
    {
        return;
    }
    if (isChoice)
    {
        if (e.key.code == sf::Keyboard::Num1)
        {
            isChoice = false;
            nextLineNumber = labelMap[choiceMap[0]];
            nextLine();
            buttonTimeout.restart();
            return;
        }

        if (e.key.code == sf::Keyboard::Num2)
        {
            isChoice = false;
            nextLineNumber = labelMap[choiceMap[1]];
            nextLine();
            buttonTimeout.restart();
            return;
        }

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
    isParsed = false;
}

void DialogueHandler::renderDialogue(sf::RenderWindow &window)
{
    window.draw(DialogueHandler::backPanel);

    if (!isParsed)
    {
        parseLine(); // stick animation into this function if any
    }
    window.draw(dialogueLineText);
    window.draw(dialogueNameText);
}

void DialogueHandler::parseLine()
{
    // std::cout << lineNumber << std::endl;
    std::string buffer = lines[lineNumber];

    std::string NPCname = "";
    std::string dialogueLine = "";
    DialogueHandler::choiceMap.clear();

    int i = 0;
    if (buffer[i] == '*')
    {
        endDialogue();
    }
    if (buffer[i] != 'L' && buffer[i] != 'J' && buffer[i] != 'C')
    {

        while (buffer[i] != 'L' && buffer[i] != 'J' && buffer[i] != 'C' && buffer[i] != '*')
        {
            lineNumber++;
            buffer = lines[lineNumber];
        }
        return;
    }
    // skipping the label if met
    if (buffer[0] == '#')
    {
        buffer = lines[lineNumber + 1];
        lineNumber = lineNumber + 1;
    }
    i = 2;

    while (buffer[i] != '$')
    {
        NPCname += buffer[i];
        i++;
    }

    if (buffer[0] == 'J')
    {
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

        std::string temp = "";
        i++;
        while (buffer[i] != ';')
        {
            temp += buffer[i];
            i++;
        }
        nextLineNumber = labelMap[temp]; // next line is right above the label
        // alter the next line adress
    }
    if (buffer[0] == 'C')
    {
        isChoice = true;
        std::string temp = "";
        i += 2;

        while (buffer[i] != ';')
        {

            while (buffer[i] != '-')
            {
                temp += buffer[i];
                i++;
            }
            DialogueHandler::choiceMap.push_back(temp);
            temp = "";
            i += 2;
            while (buffer[i] != '"')
            {
                temp += buffer[i];
                i++;
            }

            if (temp.size() > 27)
            {
                temp.insert(temp.begin() + 25, '\n');
            }

            dialogueLine += std::to_string(choiceMap.size()) + "-" + temp + '\n';
            temp = "";
            i += 2;
        }
    }
    if (buffer[0] == 'L')
    {
        isChoice = false;

        i += 2;

        int textWidth = 0; // control for wraping

        while (buffer[i] != '"')
        {
            dialogueLine += buffer[i];
            i++;
            textWidth++;
            if (textWidth == 27)
            {

                dialogueLine += '\n';
                textWidth = 0;
            }

            nextLineNumber = lineNumber + 1;
        }
    }
    isParsed = true;

    dialogueLineText.setString(dialogueLine);
    dialogueNameText.setString(NPCname);
}
