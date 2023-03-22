#include "../headers/Core/TextureHandler.hpp"

void TextureHandler::loadTexture(TextureAtlas atlas)
{
    switch (atlas)
    {
    case TextureAtlas::DA1:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Dungeon_A1.png");
        break;
        // LOTS OF CASES

    case TextureAtlas::OA2:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_A2.png");
        break;
        // LOTS OF CASES

    case TextureAtlas::IA2:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_A2.png");
        break;
        // Lots of cases
    case TextureAtlas::IA4:
        TextureHandler::textures.insert({atlas, sf::Texture()});

        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_A4.png");

        break;
    case TextureAtlas::IB0:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_B.png");
        break;

    case TextureAtlas::PRISCILLA:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/$PixelFantasy_2-Priscilla.png");
        break;
    default:
        break;
    }
}

void TextureHandler::loadAllTextures()
{
    for (int i = 0; i < TEXTURE_COUNT; i++)
    {
        loadTexture((TextureAtlas)i);
    }
}

sf::Texture &TextureHandler::getTexture(TextureAtlas atlas)
{
    return textures[atlas];
}