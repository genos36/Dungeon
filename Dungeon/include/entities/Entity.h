#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>


class Weapon;
class GameMap;
class AbstractCommunicationService;

struct Stats{
    unsigned int currentHP;
    unsigned int maxHP;
    unsigned int strenght;
    unsigned int speed;
    unsigned int CurrentStamina;
    unsigned int maxStamina;

};

enum Direction{
    UP,
    DOWN,
    RIGHT,
    LEFT
};


class Entity{
private:

Stats stats; 
Weapon* weapon;
sf::Sprite sprite;
sf::Texture texture;
GameMap* map;
sf::Vector2u position;
AbstractCommunicationService* commService;

protected:
public:
/*
Entity(const std::string& spriteFilePath="./assets/sprites/default.png", const Stats& stats={10,10,10,10,10,10});
void setSprite(const std::string& filePath);

virtual ~Entity()=default;

virtual void draw(sf::RenderWindow window)=0;
virtual void update()=0;
virtual void move(Direction direction)=0;
virtual void attack()=0;
void takeDamage();
void heal();

Stats getStats()const;
void setStats(const Stats&); 
Weapon* getWeapon()const;
sf::Vector2u getPosition()const;

*/
};


#endif