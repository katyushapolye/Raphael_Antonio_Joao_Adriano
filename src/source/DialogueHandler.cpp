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
        lineNumber++;
        buttonTimeout.restart();
    }
}
void DialogueHandler::renderDialogue(sf::RenderWindow &window)
{

    std::cout << lines[lineNumber] << std::endl;
}
