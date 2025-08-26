#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

enum class TextureType;

//use Singleton design pattern to create a common loader for textures
class TextureLoader{
    private:
    
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;    
    static TextureLoader* _instance;

    protected:
    
    TextureLoader();
    
    public:
    
    static TextureLoader* instance();
    
    // Delete copy constructor and assignment
    TextureLoader(const TextureLoader&) = delete;
    TextureLoader& operator=(const TextureLoader&) = delete;

    // Load texture with error handling
    std::shared_ptr<sf::Texture> loadTexture(const std::string& filePath);

    std::shared_ptr<sf::Texture> getTexture(const std::string& filePath);

    std::shared_ptr<sf::Texture> loadTexture(const TextureType& textureType);

    std::shared_ptr<sf::Texture> getTexture(const TextureType& textureType);

    void cleanup();

    void cleanupTexture(const std::string& filePath);
    
    void cleanupTexture(TextureType type);


};


#endif