#ifndef SINGLETEXTURELOADER_H
#define SINGLETEXTURELOADER_H

#include "AbstractTextureLoader.h"
#include <unordered_map>
#include <iostream>


class SingleTextureLoader:public AbstractTextureLoader{

    private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;  

    protected:
    SingleTextureLoader()=default;

    public:
    static const std::string NAME;


    static AbstractTextureLoader* getInstance();
    
    // Delete copy constructor and assignment
    SingleTextureLoader(const SingleTextureLoader&) = delete;
    SingleTextureLoader& operator=(const SingleTextureLoader&) = delete;

    // Load texture with error handling
    std::shared_ptr<sf::Texture> loadTexture(const std::string& filePath)override;

    std::shared_ptr<sf::Texture> getTexture(const std::string& filePath)override;

    std::shared_ptr<sf::Texture> loadTexture(const TextureType& textureType)override;

    std::shared_ptr<sf::Texture> getTexture(const TextureType& textureType)override;

    bool hasTexture(TextureType type) const override;

    void cleanup()override;

    void cleanupTexture(const std::string& filePath);
    
    void cleanupTexture(TextureType type);
};


#endif