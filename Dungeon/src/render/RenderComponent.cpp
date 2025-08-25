#include "../../include/render/RenderComponent.h"


    RenderComponent::RenderComponent(TextureType textureType,RenderLayer layer):
    textureType(textureType),layer(layer),visible(true),
    color(sf::Color::White),rotation(0.f),scale(1.f,1.f),opacity(0.5f),flipX(false),flipY(false){
        auto texture (TextureLoader::instance()->loadTexture(textureType));

        if(texture){
            textureRect=sf::IntRect(0,0,texture->getSize().x,texture->getSize().y);
        }
    }


    sf::Sprite RenderComponent::createSprite(const sf::Vector2f& worldPosition) const{

        if(!visible){
            return sf::Sprite();
        }

        auto texture =TextureLoader::instance()->loadTexture(textureType);
        if(!texture){
            return sf::Sprite();            
        }

        sf::Sprite sprite(*texture,textureRect);

        sprite.setPosition(worldPosition+offset);
        sprite.setColor(color);
        sprite.setRotation(rotation);
        sprite.setScale(scale);
        sprite.setScale(
            flipX?abs(scale.x)*-1:scale.x,
            flipY?abs(scale.y)*-1:scale.y
        );

        return sprite;
    }

    void RenderComponent::draw(sf::RenderTarget& target, const sf::Vector2f& worldPosition) const{
        target.draw(createSprite(worldPosition));
    }

    void RenderComponent::setColor(const sf::Color& color){
        this->color=color;
    }

    const sf::Color& RenderComponent::getColor() const{
        return color;
    }

    void RenderComponent::setOpacity(float opacity){
        this->opacity=opacity;
    }

    float RenderComponent::getOpacity() const{
        return opacity;
    }

    void RenderComponent::setFlip(bool flipX, bool flipY){
        this->flipX=flipX;
        this->flipY=flipY;
    }

    void RenderComponent::getFlip(bool& flipX, bool& flipY) const{
        flipX=this->flipX;
        flipY=this->flipY;
    }

    void RenderComponent::setRotation(float degrees){
        this->rotation=rotation;
    }

    float RenderComponent::getRotation() const{
        return rotation;
    }

    void RenderComponent::setScale(const sf::Vector2f& scale){
        this->scale=scale;
    }

    const sf::Vector2f& RenderComponent::getScale() const{
        return scale;
    }

    void RenderComponent::setOffset(const sf::Vector2f& offset){
        this->offset=offset;
    }

    const sf::Vector2f& RenderComponent::getOffset() const{
        return offset;
    }
    void RenderComponent::addAnimation(const std::vector<sf::IntRect>& frames,
                     AnimationID id, 
                     float frameTime, 
                     bool loop ) {
        animationSystem.addAnimation(frames, id, frameTime, loop);
    }
    
    void RenderComponent::playAnimation(AnimationID id, bool restart ) {
        animationSystem.playAnimation(id, restart);
        updateTextureRectFromAnimation();
    }
    
    void RenderComponent::stopAnimation() {
        animationSystem.stopAnimation();
    }
    
    void RenderComponent::updateAnimation(float deltaTime) {
        animationSystem.updateAnimation(deltaTime);
        updateTextureRectFromAnimation();
    }
    
    bool RenderComponent::isPlayingAnimation() const {
        return animationSystem.isPlayingAnimation();
    }
    
    AnimationID RenderComponent::getCurrentAnimationID() const {
        return animationSystem.getCurrentAnimationID();
    }

    void RenderComponent::updateTextureRectFromAnimation() {
        textureRect = animationSystem.getCurrentFrameRect();
    }