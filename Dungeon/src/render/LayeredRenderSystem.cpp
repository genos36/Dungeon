#include "../../include/render/LayeredRenderSystem.h"


LayeredRenderSystem::LayeredRenderSystem(sf::RenderWindow* window):window(window){
    renderLayers.resize(static_cast<size_t>(RenderLayer::COUNT));

    for(size_t i=0;i<static_cast<size_t>(RenderLayer::COUNT);++i){
        renderLayers[i]=(std::vector<sf::Sprite>());
        renderLayers[i].reserve(INITIAL_LAYER_CAPACITY);
    }
}

void LayeredRenderSystem::addToLayer(RenderLayer layer, const sf::Sprite& sprite){
    if(static_cast<size_t>(layer)<renderLayers.size())
    renderLayers[static_cast<size_t>(layer)].push_back(sprite);
}



void LayeredRenderSystem::renderAll() {
    if(!window)return;
    // Iterate through layers in order - super fast!
    for (auto& layer : renderLayers) {
        for (auto& sprite : layer) {
            window->draw(sprite);
        }
        layer.clear(); // Clear vectors for next frame
    }
}

size_t LayeredRenderSystem::getLayerCount(RenderLayer layer) const {
    return (static_cast<size_t>(layer) < renderLayers.size()) ? 
        renderLayers[static_cast<size_t>(layer)].size() : 0;
}

size_t LayeredRenderSystem::getTotalDrawCalls() const {
    size_t total = 0;
    for (const auto& layer : renderLayers) {
        total += layer.size();
    }
    return total;
}


void LayeredRenderSystem::beginFrame(){
    window->clear(sf::Color::Black);
}

void LayeredRenderSystem::endFrame(){
    window->display();
}

