#include "render/TextureLoaderStrategy/SingleTextureLoader.h"
#include "render/TextureRegistry.h"


const std::string SingleTextureLoader::NAME("SingleTextureLoader");



AbstractTextureLoader* SingleTextureLoader::getInstance(){
    auto ptr=AbstractTextureLoader::lookUp(NAME);
    if(ptr==nullptr){
        static SingleTextureLoader instance;
        AbstractTextureLoader::Register(NAME,&instance);
    }
    return ptr ;
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
    
    bool SingleTextureLoader::hasTexture(TextureType type) const {
        try{
            textures.at(TextureRegistry::getTexturePath(type));
            return true;
        }
        catch(std::out_of_range){
            return false;
        }
    }