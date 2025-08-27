#include "render/TextureLoaderStrategy/SingleTextureLoader.h"
#include "render/TextureRegistry.h"

SingleTextureLoader::SingleTextureLoader(){
}


AbstractTextureLoader* SingleTextureLoader::getInstance(){
    if(Singleton::lookUp(NAME)==nullptr){
        Singleton::Register(NAME,new SingleTextureLoader());
    }
    return dynamic_cast<AbstractTextureLoader*>(Singleton::lookUp(NAME)) ;
}


    std::shared_ptr<sf::Texture> SingleTextureLoader::loadTexture(const std::string& filePath){
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
    
    std::shared_ptr<sf::Texture> SingleTextureLoader::getTexture(const std::string& filePath){
        auto it=textures.find(filePath);
        if(it!=textures.end()){
            return it->second;
        }
        return loadTexture(filePath);
    }

    void SingleTextureLoader::cleanup(){
        textures.clear();
        // delete _instance;
        // _instance=nullptr;
    }



    std::shared_ptr<sf::Texture> SingleTextureLoader::loadTexture(const TextureType& textureType){
        return loadTexture(TextureRegistry::getTexturePath(textureType));
    }

    std::shared_ptr<sf::Texture> SingleTextureLoader::getTexture(const TextureType& textureType){
        return getTexture(TextureRegistry::getTexturePath(textureType));
    }

    void SingleTextureLoader::cleanupTexture(TextureType type) {
    cleanupTexture(TextureRegistry::getTexturePath(type));
    }


    void SingleTextureLoader::cleanupTexture(const std::string& filePath) {
        textures.erase(filePath);
    }
    