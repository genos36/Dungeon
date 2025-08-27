#include "../../../include/render/CullingStrategy/NoCullingStrategy.h"

bool NoCullingStrategy::shouldRender(const sf::Sprite & sprite, const Camera* camera)const {
    return true;
}
