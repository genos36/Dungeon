#ifndef TEXTUREREGISTRY_H
#define TEXTUREREGISTRY_H

#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <exception>

enum class TextureType{
    // Tiles
    TILE_GRASS=0,
    TILE_WATER,
    TILE_STONE,
    TILE_ROCK,
    TREE,


    COUNT           //MUST BE LAST
};

class TextureRegistry{
private:
    static inline std::vector<std::string> registry = {
        // Tiles
        {"./assets/sprites/terrain/grass.png"},
        {"./assets/sprites/terrain/water.png"},
        {"./assets/sprites/terrain/rock.png"},
        {"./assets/sprites/terrain/dirt.png"},
        {"./assets/sprites/terrain/tree.png"}
    };
    
    // Compile-time size validation
    static_assert(static_cast<size_t>(TextureType::COUNT) ==5,
                 "TextureType enum changed! Update TextureRegistry initialization.");
public:
    TextureRegistry()=delete;
    static std::string getTexturePath(TextureType type);
    

    // static void registerTexture(TextureType type, const std::string& path);
};
#endif

