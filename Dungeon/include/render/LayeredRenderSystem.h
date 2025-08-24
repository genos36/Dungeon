#ifndef LAYEREDRENDERSYSTEM_H
#define LAYEREDRENDERSYSTEM_H

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

enum class RenderLayer {
    BACKGROUND=0,
    TILES,
    ENTITIES,
    ITEMS,
    EFFECTS,
    UI,
    DEBUG,
    
    COUNT // Automatically becomes the size (excluding this element)
};


class LayeredRenderSystem{
private: 
    sf::RenderWindow* window;
    std::vector<std::vector<sf::Sprite>> renderLayers;
public:
    static constexpr float TILE_SIDE=32.0f; 
    static constexpr size_t INITIAL_LAYER_CAPACITY = 512;

    LayeredRenderSystem(sf::RenderWindow* window);

    void addToLayer(RenderLayer layer,const sf::Sprite& sprite);
    void renderAll();

    size_t getLayerCount(RenderLayer layer) const;
    size_t getTotalDrawCalls() const;

    void beginFrame();
    void endFrame();
    

};






#endif