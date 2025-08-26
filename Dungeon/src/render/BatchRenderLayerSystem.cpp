#include "../../include/render/BatchRenderLayerSystem.h"

BatchRenderLayerSystem::BatchRenderLayerSystem(sf::RenderWindow* win):
    window(win),layers(static_cast<size_t>(RenderLayer::COUNT)),batchRenderer(win){}

void BatchRenderLayerSystem::beginFrame(){
    window->clear(sf::Color::Black);
    batchRenderer.begin();
}

void BatchRenderLayerSystem::endFrame(){
    batchRenderer.end();
    window->display();
}

void BatchRenderLayerSystem::addToLayer(RenderLayer layer, const sf::Sprite& sprite){
    if(static_cast<size_t>(layer)<layers.size())
        layers[static_cast<size_t>(layer)].push_back(sprite);
}

void BatchRenderLayerSystem::renderLayer(RenderLayer layer){
    if(static_cast<size_t>(layer)<layers.size()){

        for(sf::Sprite sprite : layers[static_cast<size_t>(layer)]){
            batchRenderer.addSprite(sprite);
        }
        batchRenderer.end();
        clearLayer(layer);
    }
}

 
void BatchRenderLayerSystem::renderAll(){
    if(static_cast<size_t>(RenderLayer::COUNT)==layers.size())
        for(size_t i=0; i<static_cast<size_t>(RenderLayer::COUNT);++i){
            renderLayer(static_cast<RenderLayer>(i));    
        }
        batchRenderer.end();    // End batch once
        clearAllLayers();
}

size_t BatchRenderLayerSystem::getLayerCount(RenderLayer layer) const{
        if(static_cast<size_t>(layer)<layers.size()){
            return layers[static_cast<size_t>(layer)].size();
        }
        else{
            return 0;
        }
}

size_t BatchRenderLayerSystem::getTotalDrawCalls() const{
    size_t sum=0;
    for(auto layer:layers){
        sum+=layer.size();
    }
    return sum;
}

void BatchRenderLayerSystem::clearLayer(RenderLayer layer){
    if(static_cast<size_t>(layer)<layers.size()){
        layers[static_cast<size_t>(layer)].clear();
    }
}

void BatchRenderLayerSystem::clearAllLayers(){
    for(auto layer:layers){
        layer.clear();
    }
}