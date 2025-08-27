#ifndef NOCULLINGSTRATEGY_H
#define NOCULLINGSTRATEGY_H
#include "AbstractCullingStrategy.h"

class NoCullingStrategy : public AbstractCullingStrategy{
public:

bool shouldRender(const sf::Sprite & sprite, const Camera* camera)const override;

};


#endif