#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics.hpp>
#include "TextureLoader.h"
#include "TextureRegistry.h"

class RenderSystem{
private:
    static constexpr float TILE_SIDE=32.0f; 
    sf::RenderWindow* window;


public:

    RenderSystem(sf::RenderWindow* window=nullptr);

    void drawSprite(TextureType type, const sf::Vector2f& position, 
                   const sf::IntRect& textureRect = sf::IntRect(0.0f,0.0f,TILE_SIDE,TILE_SIDE));

    void drawTile(TextureType type, const sf::Vector2f& position);

    void beginFrame();
    void endFrame();
    

};


#endif