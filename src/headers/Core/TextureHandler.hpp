#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>
#include <unordered_map>

#define TEXTURE_COUNT 31
class TextureHandler
{

public:
    enum TextureAtlas
    {
        DA1,
        DA2,
        DA4,
        DA5,
        IA1,
        IA2,
        IA4,
        IA5,
        OA1,
        OA2,
        OA3,
        OA4,
        OA5,
        OB0,
        OC0,
        OD0,
        IB0,
        IC0,
        ID0,
        FC1,
        FC2,
        FC3,
        MC1,
        MC2,
        MC3,
        REID,
        PRISCILLA,
        GALE,
        MICHELLE,
        ICONS,
        WINDOW
    };

private:
    static inline std::unordered_map<TextureAtlas, sf::Texture> textures = {};

public:
    // static bool unloadTexture(TextureAtlas atlas);
    static void loadTexture(TextureAtlas atlas);
    static void loadAllTextures();

    static sf::Texture &getTexture(TextureAtlas atlas);
};

#endif