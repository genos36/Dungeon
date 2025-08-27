#include "Utilities/Singleton.h"


Singleton* Singleton::instance=nullptr;

Singleton* Singleton::lookUp(const char* name){
    if(registry.at(name)==0)return nullptr;

    return registry[name];

}

void Singleton::Register(const char* name,Singleton* subclassInstance){
    if(instance==nullptr)getInstance();
    registry[name]=subclassInstance;
}

Singleton* Singleton::getInstance(){
    if(instance==nullptr){
        instance=new Singleton();
        Register("Singleton",instance);
    }
    return instance;
}

Singleton::~Singleton(){
    delete instance;
    instance=nullptr;
}