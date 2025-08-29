#include "render/TextureLoaderStrategy/AbstractTextureLoader.h"



//construct-on-first-use idiom
std::map<std::string, AbstractTextureLoader*>& AbstractTextureLoader::getRegistry() {
    static std::map<std::string, AbstractTextureLoader*> registry;
    return registry;
}



AbstractTextureLoader* AbstractTextureLoader::lookUp(std::string name){
    auto it=getRegistry().find(name);
    if(it==getRegistry().end())return nullptr;

    return it->second;

}

void AbstractTextureLoader::Register(std::string name,AbstractTextureLoader* loader){
    getRegistry()[name]=loader;
}