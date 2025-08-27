#ifndef CULLEDRENDERSYSTEM_H
#define CULLEDRENDERSYSTEM_H
#include "BatchRenderLayerSystem.h"
#include "Camera.h"

class AbstractCullingStrategy;


//refined batch render system, use composition of various concepts to improve performance
class CulledRenderSystem{
    private:
    BatchRenderLayerSystem renderSystem;
    Camera* camera;
    //strategy pattern to handle culling
    std::unique_ptr<AbstractCullingStrategy> cullingStrategy;
    public:
    CulledRenderSystem(sf::RenderWindow* window, Camera* cameraView=nullptr);

    void setCamera(Camera* camera);
    void setCullingStrategy(std::unique_ptr<AbstractCullingStrategy> strategy);

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