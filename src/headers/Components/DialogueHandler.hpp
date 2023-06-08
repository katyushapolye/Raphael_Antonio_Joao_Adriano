#ifndef DIALOGUEHANDLER_H
#define DIALOGUEHANDLER_H
#include <iostream>
#include <map>
#include <fstream>
#include "../Core/Game.hpp"

class DialogueHandler
{
private:
    static inline int lineNumber;
    static inline std::map<std::string, int> labelMap;
    static inline std::vector<std::string> lines;

    static inline sf::Clock buttonTimeout;

public:
    static void receiveInput(sf::Event e);
    static void startDialogue(std::string dialogueName);
    static void renderDialogue(sf::RenderWindow &window);
};
#endif
