#ifndef DIALOGUEHANDLER_H
#define DIALOGUEHANDLER_H
#include <iostream>
#include <map>
#include <fstream>
#include "../Core/Game.hpp"
#include <stdio.h>
#include <string.h>

class DialogueHandler
{
private:
    static inline int lineNumber;
    static inline std::map<std::string, int> labelMap;
    static inline std::vector<std::string> lines;

    static inline sf::Clock buttonTimeout;

    // Control
    static inline bool isChoice = false;
    static inline bool isJump = false;

    static inline int nextLineNumber = 1;

    // UI

    static inline sf::Sprite backPanel;
    static inline sf::Text dialogueLineText;
    static inline sf::Text dialogueNameText;

    static std::string parseLine();

    static void nextLine();

public:
    static void receiveInput(sf::Event e);
    static void startDialogue(std::string dialogueName);
    static void renderDialogue(sf::RenderWindow &window);
};
#endif
