#ifndef CONSERVATIVEFRUSTUMCALLING_H
#define CONSERVATIVEFRUSTUMCALLING_H
#include "AbstractCullingStrategy.h"

class ConservativeFrustumCulling : public AbstractCullingStrategy{

private:
float expansionFactor;

public:
    ConservativeFrustumCulling(float expansionFactor=1.4f);
    void adaptToView(const Camera* camera);
    bool shouldRender(const sf::Sprite & sprite, const Camera* camera)const override;

};


#endif