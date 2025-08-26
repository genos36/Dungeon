#ifndef BATCHRENDERLAYERSYSTEM_H
#define BATCHRENDERLAYERSYSTEM_H

#include <SFML/Graphics.hpp>
#include "LayeredRenderSystem.h"
#include "BatchRenderer.h"

class BatchRenderLayerSystem {
private:
    sf::RenderWindow* window;
    std::vector<std::vector<sf::Sprite>> layers;
    BatchRenderer batchRenderer;
    
public:
    BatchRenderLayerSystem(sf::RenderWindow* win);

    
    void beginFrame();
    void endFrame();

    void addToLayer(RenderLayer layer, const sf::Sprite& sprite);
    void renderLayer(RenderLayer layer);
    void renderAll();

    void clearLayer(RenderLayer layer);
    void clearAllLayers();

    size_t getLayerCount(RenderLayer layer) const;
    size_t getTotalDrawCalls() const;
};

#endif