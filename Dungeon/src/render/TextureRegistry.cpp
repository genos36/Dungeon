#include "../../include/render/TextureRegistry.h"


std::string TextureRegistry::getTexturePath(TextureType type) {

        if (static_cast<size_t>(type)<registry.size()) 
                return registry[static_cast<size_t>(type)];
        
                // Fallback for invalid indices
        std::cerr << "Error: Texture type " << static_cast<int>(type) 
                  << " not registered. Using default texture." << std::endl;
        return "assets/sprites/terrain/default.png";
    }

    // void TextureRegistry::registerTexture(TextureType type, const std::string& path) {
    //     registry[static_cast<size_t>(type)] = path;
    // }