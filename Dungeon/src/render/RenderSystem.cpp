#include "../../include/render/RenderSystem.h"



RenderSystem::RenderSystem(sf::RenderWindow* window):
    window(window){}

void RenderSystem::beginFrame(){
    window->clear(sf::Color::Black);
}


void RenderSystem::endFrame(){
    window->display();
}

void RenderSystem::drawSprite(TextureType type, const sf::Vector2f& position, 
                   const sf::IntRect& textureRect){
    auto texture =TextureLoader::instance()->getTexture(type);
    if(texture==nullptr){
       return; 
    }
    sf::Sprite sprite(*texture);
    sprite.setPosition(position);
    
    if(textureRect!=sf::IntRect()){
        sprite.setTextureRect(textureRect);
    }
    window->draw(sprite);

    }

    void RenderSystem::drawTile(TextureType tileType, const sf::Vector2f& position) {
        drawSprite(tileType, position);
    }