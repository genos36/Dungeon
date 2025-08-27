#include "render/CulledRenderSystem.h"
#include "render/CullingStrategy/AbstractCullingStrategy.h"

    CulledRenderSystem::CulledRenderSystem(sf::RenderWindow* window, Camera* camera):
    renderSystem(window),camera(camera),cullingStrategy(nullptr){}

    void CulledRenderSystem::setCamera(Camera* camera){
        this->camera=camera;
    }
    void CulledRenderSystem::setCullingStrategy(std::unique_ptr<AbstractCullingStrategy> strategy){
        cullingStrategy=std::move(strategy);
    }

    void CulledRenderSystem::beginFrame(){
        renderSystem.beginFrame();
    }
    void CulledRenderSystem::endFrame(){
        renderSystem.endFrame();
    }

    void CulledRenderSystem::addToLayer(RenderLayer layer, const sf::Sprite& sprite){
        if(cullingStrategy && camera && cullingStrategy->shouldRender(sprite,camera)){
            renderSystem.addToLayer(layer,sprite);
        }


    }

    void CulledRenderSystem::renderAll(){
        renderSystem.renderAll();
    }

    void CulledRenderSystem::renderLayer(RenderLayer layer){
        renderSystem.renderLayer(layer);
    }

    void CulledRenderSystem::clearLayer(RenderLayer layer){
        renderSystem.clearLayer(layer);
    }

    void CulledRenderSystem::clearAllLayers(){
        renderSystem.clearAllLayers();
    }

    size_t CulledRenderSystem::getLayerCount(RenderLayer layer) const{
        return renderSystem.getLayerCount(layer);
    }

    size_t CulledRenderSystem::getTotalDrawCalls() const{
        return renderSystem.getTotalDrawCalls();
    }