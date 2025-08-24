#ifndef ABSTRACTCOMMUNICATIONSERVICE_H 
#define ABSTRACTCOMMUNICATIONSERVICE_H 

#include <SFML/Graphics.hpp>

class Entity;


class AbstactCommunicationService {
public:
    virtual ~AbstactCommunicationService() = default;
    
    // Movement
    virtual bool canMoveTo(Entity* entity, sf::Vector2u newPos) = 0;
    virtual void onMove(Entity* entity, sf::Vector2u from, sf::Vector2u to) = 0;
    
    // Combat
    virtual bool canAttack(Entity* attacker, Entity* target) = 0;
    virtual void onAttack(Entity* attacker, Entity* target) = 0;
    virtual void onDamage(Entity* target, int damage) = 0;
    virtual void onDeath(Entity* entity) = 0;
    
    // Interactions
    virtual void onTileInteraction(Entity* entity, sf::Vector2u position) = 0;
    //virtual void onItemPickup(Entity* entity, Item* item) = 0;
    

};




#endif