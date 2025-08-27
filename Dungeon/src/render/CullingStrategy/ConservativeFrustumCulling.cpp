#include "../../../include/render/CullingStrategy/ConservativeFrustumCulling.h"

ConservativeFrustumCulling::ConservativeFrustumCulling(float expansionFactor):
    expansionFactor(expansionFactor){}



bool ConservativeFrustumCulling::shouldRender(const sf::Sprite & sprite, const Camera* camera)const {
    sf::Vector2f viewSize = camera->getView().getSize();
    sf::Vector2f viewCenter = camera->getView().getCenter();
    
    // Expand view bounds
    sf::FloatRect expandedBounds(
        viewCenter - (viewSize * expansionFactor) / 2.f,
        viewSize * expansionFactor
    );
    
    return expandedBounds.intersects(sprite.getGlobalBounds());
}

void ConservativeFrustumCulling::adaptToView(const Camera* camera){
    if(!camera)return;
    // Dynamic expansion based on camera movement speed
    float speedFactor = std::min(camera->getMoveSpeed() * 0.5f, 3.0f);
    
    // Also consider zoom level - expand more when zoomed out
    float zoomFactor = std::max(1.0f / camera->getZoom(), 1.0f);
    
    expansionFactor = 1.2f * speedFactor * zoomFactor;
}