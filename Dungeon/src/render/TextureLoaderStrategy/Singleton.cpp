#include "render/TextureLoaderStrategy/Singleton.h"

// #include "Render/TextureLoaderStrategy/AbstractTextureLoader.h"

Singleton* Singleton::instance=nullptr;
std::map<std::string, AbstractTextureLoader*> Singleton::registry;

AbstractTextureLoader* Singleton::lookUp(std::string name){
    // if(registry.at(name)==0)return nullptr;

    // return registry[name];
    try{
        registry.at(name);
        return registry[name];
    }
    catch(std::out_of_range){
        return nullptr;
    }
}

void Singleton::Register(std::string name,AbstractTextureLoader* subclassInstance){
    if(instance==nullptr)getInstance();
    registry[name]=subclassInstance;
}

Singleton* Singleton::getInstance(){
    static Singleton instance=Singleton();
    return &instance;
}
