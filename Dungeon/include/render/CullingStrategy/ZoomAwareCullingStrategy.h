#ifndef ZOOMAWARECULLINGSTRATEGY_H
#define ZOOMAWARECULLINGSTRATEGY_H

#include"AbstractCullingStrategy.h"
#include <SFML/Graphics.hpp>

class ZoomAwareCullingStrategy :public AbstractCullingStrategy{
private:
    float baseCullingFactor;
    
public:
    ZoomAwareCullingStrategy(float baseFactor = 1.0f) ;
    
    bool shouldRender(const sf::Sprite& sprite, const Camera* camera) const override;

};
#endif