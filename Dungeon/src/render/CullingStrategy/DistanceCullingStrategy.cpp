#include "render/CullingStrategy/DistanceCullingStrategy.h"
#include "render/Camera.h"

    DistanceCullingStrategy::DistanceCullingStrategy(float maxDistance ) :
     maxRenderDistance(maxDistance) {}

    bool DistanceCullingStrategy::shouldRender(const sf::Sprite& sprite, const Camera* camera) const  {
        if (!camera) return true;
        sf::Vector2f ViewPosition(camera->getCurrentPosition());
        // Calculate distance from camera to sprite
        float distance = std::sqrt(
            std::pow(sprite.getPosition().x - ViewPosition.x, 2) +
            std::pow(sprite.getPosition().y - ViewPosition.y, 2)
        );
        
        return distance <= maxRenderDistance;
    }