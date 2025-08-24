#include "../../include/render/TextureLoader.h"
#include "../../include/render/TextureRegistry.h"
#include <iostream>
TextureLoader* TextureLoader::_instance=nullptr;

TextureLoader* TextureLoader::instance(){
    if(_instance==nullptr){
        _instance=new TextureLoader;
    }
    return _instance;
}

TextureLoader::TextureLoader(){}



    std::shared_ptr<sf::Texture> TextureLoader::loadTexture(const std::string& filePath){
        if(textures.find(filePath)!=textures.end()){
            return textures[filePath];
        }

        auto texture=std::make_shared<sf::Texture>();
        if(!texture->loadFromFile(filePath)){
            std::cerr<<"Failed to load texture: " << filePath << std::endl;
            return nullptr;
        }
        texture->setSmooth(true);
        textures[filePath]=texture;
        return texture;

    }
    
    std::shared_ptr<sf::Texture> TextureLoader::getTexture(const std::string& filePath){
        auto it=textures.find(filePath);
        if(it!=textures.end()){
            return it->second;
        }
        return loadTexture(filePath);
    }

    void TextureLoader::cleanup(){
        textures.clear();
        // delete _instance;
        // _instance=nullptr;
    }



    std::shared_ptr<sf::Texture> TextureLoader::loadTexture(const TextureType& textureType){
        return loadTexture(TextureRegistry::getTexturePath(textureType));
    }

    std::shared_ptr<sf::Texture> TextureLoader::getTexture(const TextureType& textureType){
        return getTexture(TextureRegistry::getTexturePath(textureType));
    }

    void TextureLoader::cleanupTexture(TextureType type) {
    cleanupTexture(TextureRegistry::getTexturePath(type));
    }


    void TextureLoader::cleanupTexture(const std::string& filePath) {
        textures.erase(filePath);
    }
    