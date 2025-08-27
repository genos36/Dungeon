#ifndef SINGLETON_H
#define SINGLETON_H
#include <map>

class Singleton{
    private:
        static Singleton* instance;
        static std::map<const char*, Singleton*>registry;
        protected:
        virtual ~Singleton();
        Singleton()=default;
        static Singleton* lookUp(const char* name);
    public:
        static void Register(const char* name,Singleton*);
        static Singleton* getInstance();



        Singleton(const Singleton&)=delete;
        Singleton& operator=(const Singleton&)=delete;
};



#endif