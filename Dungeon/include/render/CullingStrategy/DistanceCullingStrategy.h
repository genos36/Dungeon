#ifndef DISTANCECULLINGSTRATEGY_H
#define DISTANCECULLINGSTRATEGY_H

#include "AbstractCullingStrategy.h"

class DistanceCullingStrategy : public AbstractCullingStrategy {
private:
    float maxRenderDistance;
    
public:
    DistanceCullingStrategy(float maxDistance = 1000.0f);
    
    bool shouldRender(const sf::Sprite& sprite, const Camera* camera) const override;
};
#endif