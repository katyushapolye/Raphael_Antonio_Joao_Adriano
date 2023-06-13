#include "../headers/Core/TextureHandler.hpp"

void TextureHandler::loadTexture(TextureAtlas atlas)
{
    switch (atlas)
    {
        // CASES OF DUNGEONS

    case TextureAtlas::DA1:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Dungeon_A1.png");
        break;

    case TextureAtlas::DA2:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Dungeon_A2.png");
        break;

    case TextureAtlas::DA4:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Dungeon_A4.png");
        break;

    case TextureAtlas::DA5:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Dungeon_A5.png");
        break;

        // CASES OF OUTSIDE PLACES

    case TextureAtlas::OA1:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_A1.png");
        break;

    case TextureAtlas::OA2:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_A2.png");
        break;

    case TextureAtlas::OA3:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_A3.png");
        break;

    case TextureAtlas::OA4:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_A4.png");
        break;

    case TextureAtlas::OA5:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_A5.png");
        break;

    case TextureAtlas::OB0:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_B.png");
        break;

    case TextureAtlas::OC0:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_C.png");
        break;

    case TextureAtlas::OD0:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Outside_D-Trees.png");
        break;

        // CASES OF INSIDE PLACES

    case TextureAtlas::IA1:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_A1.png");
        break;

    case TextureAtlas::IA2:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_A2.png");
        break;

    case TextureAtlas::IA4:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_A4.png");
        break;

    case TextureAtlas::IA5:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_A5.png");
        break;

        // CASES OF ALTERNATIVE INSIDE PLACES

    case TextureAtlas::IB0:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_B.png");
        break;

    case TextureAtlas::IC0:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_C.png");
        break;

    // case TextureAtlas::ID0:
    //     TextureHandler::textures.insert({atlas, sf::Texture()});
    //     textures[atlas].loadFromFile("Resources/tilesets/PixelFantasy_Inside_D.png");
    //     break;

        // CASES OF CHARACTERS

    case TextureAtlas::REID:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/$PixelFantasy_1-Reid.png");
        break;

    case TextureAtlas::PRISCILLA:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/$PixelFantasy_2-Priscilla.png");
        break;

    case TextureAtlas::MICHELLE:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/$PixelFantasy_4-Michelle.png");
        break;

    case TextureAtlas::GALE:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/$PixelFantasy_3-Gale.png");
        break;

    case TextureAtlas::MC1:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/MCharacter1.png");
        break;

    case TextureAtlas::MC2:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/MCharacter2.png");
        break;

    case TextureAtlas::MC3:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/MCharacter3.png");
        break;

    case TextureAtlas::FC1:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/FCharacter1.png");
        break;

    case TextureAtlas::FC2:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/FCharacter2.png");
        break;

    case TextureAtlas::FC3:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/characters/FCharacter3.png");
        break;

        // CASES OF HUD AND ITEMS

    case TextureAtlas::ICONS:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/system/IconSet.png");
        break;

    case TextureAtlas::WINDOW:
        TextureHandler::textures.insert({atlas, sf::Texture()});
        textures[atlas].loadFromFile("Resources/system/Window.png");

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