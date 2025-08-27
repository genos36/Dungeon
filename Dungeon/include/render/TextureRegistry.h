#ifndef TEXTUREREGISTRY_H
#define TEXTUREREGISTRY_H

#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include "TextureLoaderStrategy/TextureType.h"



class TextureRegistry{
private:
//ON_UPDATE
    static inline std::vector<std::string> registry = {
        // Tiles
        {"./assets/sprites/terrain/grass.png"},
        {"./assets/sprites/terrain/water.png"},
        {"./assets/sprites/terrain/rock.png"},
        {"./assets/sprites/terrain/dirt.png"},
        {"./assets/sprites/terrain/tree.png"}
    };

//ON_UPDATE
    // Compile-time size validation,
    static_assert(static_cast<size_t>(TextureType::COUNT) ==5,
                 "TextureType enum changed! Update TextureRegistry initialization.");
public:
    TextureRegistry()=delete;
    static std::string getTexturePath(TextureType type);
    

    // static void registerTexture(TextureType type, const std::string& path);
};
#endif

