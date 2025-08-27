#ifndef ABSTRACTCULLINGSTRATEGY_H
#define ABSTRACTCULLINGSTRATEGY_H
#include "../BatchRenderLayerSystem.h"
#include "../Camera.h"

//strategy pattern for culling
class AbstractCullingStrategy{
public:
virtual ~AbstractCullingStrategy()=default;

virtual bool shouldRender(const sf::Sprite & sprite, const Camera* camera)const =0;



};

#endif