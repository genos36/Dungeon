#include "../../../include/render/CullingStrategy/ZoomAwareCullingStrategy.h"

ZoomAwareCullingStrategy::ZoomAwareCullingStrategy(float baseFactor ): baseCullingFactor(baseFactor) {}


    bool ZoomAwareCullingStrategy::shouldRender(const sf::Sprite& sprite, const Camera* camera) const {
        if (!camera) return true;
        
        // Get current zoom level
        float zoomLevel = camera->getZoom();
        
        // More aggressive culling when zoomed out
        float effectiveCulling = baseCullingFactor / zoomLevel;
        
        // Calculate dynamic view bounds
        sf::FloatRect viewBounds = camera->getViewBounds();
        sf::FloatRect scaledBounds(
            viewBounds.left - viewBounds.width * effectiveCulling,
            viewBounds.top - viewBounds.height * effectiveCulling,
            viewBounds.width * (1 + 2 * effectiveCulling),
            viewBounds.height * (1 + 2 * effectiveCulling)
        );
        
        return scaledBounds.intersects(sprite.getGlobalBounds());
    }