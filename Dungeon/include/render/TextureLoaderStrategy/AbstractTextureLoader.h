#ifndef ABSTRACTTEXTURELOADER_H
#define ABSTRACTTEXTURELOADER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "TextureType.h"
#include <map>
#include "Singleton.h"


class AbstractTextureLoader:public Singleton{
public:
    virtual ~AbstractTextureLoader()=default;
//strategy pattern methods
    // Load texture with error handling
    virtual std::shared_ptr<sf::Texture> loadTexture(const std::string& filePath)=0;

    virtual std::shared_ptr<sf::Texture> getTexture(const std::string& filePath)=0;

    virtual std::shared_ptr<sf::Texture> loadTexture(const TextureType& textureType)=0;

    virtual std::shared_ptr<sf::Texture> getTexture(const TextureType& textureType)=0;
    
    virtual bool hasTexture(TextureType type) const = 0;

    virtual void cleanup() = 0;
    // sf::Sprite createSprite(const TextureType& textureType ,const sf::IntRect& textureRect ,const sf::Vector2f& worldPosition);
};


#endif