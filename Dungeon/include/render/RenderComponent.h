#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#pragma once
#include <SFML/Graphics.hpp>
#include "TextureRegistry.h"
#include "TextureLoader.h"
#include "LayeredRenderSystem.h"
#include "AnimationSystem.h"

//A component that gives entities their visual representation, separating rendering logic from game logic.
class RenderComponent{

private:
    // Core properties
    TextureType textureType;
    sf::IntRect textureRect;
    sf::Vector2f offset;
    RenderLayer layer;
    bool visible;
    sf::Color color;
    float rotation;
    sf::Vector2f scale;
    float opacity;
    
    // Enhanced features
    bool flipX, flipY;
    // Animation system
    AnimationSystem animationSystem;
/*    
    sf::Shader* shader;
    sf::BlendMode blendMode;

    
    // State system
    std::map<std::string, std::pair<sf::Color, std::string>> stateVisuals;
    std::string currentState;
    
    // Helper methods
    sf::Color applyOpacity(const sf::Color& baseColor) const;
    void updateTextureRectFromAnimation();
*/
public:
    RenderComponent(TextureType textureType=TextureType::TILE_GRASS,
                     RenderLayer layer=RenderLayer::ENTITIES);

    // Core functionality
    sf::Sprite createSprite(const sf::Vector2f& worldPosition) const;
    void draw(sf::RenderTarget& target, const sf::Vector2f& worldPosition) const;    

    // Property accessors
    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;
    void setOpacity(float opacity);
    float getOpacity() const;
    
    // Transformations
    void setFlip(bool flipX, bool flipY);
    void getFlip(bool& flipX, bool& flipY) const;
    void setRotation(float degrees);
    float getRotation() const;
    void setScale(const sf::Vector2f& scale);
    const sf::Vector2f& getScale() const;
    void setOffset(const sf::Vector2f& offset);
    const sf::Vector2f& getOffset() const;
    
    // Animation
    void addAnimation(const std::vector<sf::IntRect>& frames,
                     AnimationID id, 
                     float frameTime = 0.1f, 
                     bool loop = true);
    
    void playAnimation(AnimationID id, bool restart = false) ;
    
    void stopAnimation() ;
    
    void updateAnimation(float deltaTime) ;
    
    bool isPlayingAnimation() const ;
    
    AnimationID getCurrentAnimationID() const ;

    /*
    void addAnimation(const std::string& name, const std::vector<sf::IntRect>& frames, 
                     float frameTime, bool loop = true);
    void playAnimation(const std::string& name, bool restart = false);
    void stopAnimation();
    void updateAnimation(float deltaTime);
    bool isPlayingAnimation() const;
    
    // Advanced effects
    void setShader(sf::Shader* shader);
    sf::Shader* getShader() const;
    void setBlendMode(sf::BlendMode mode);
    sf::BlendMode getBlendMode() const;
    
    // Visibility and ordering
    void setVisible(bool visible);
    bool isVisible() const;
    void setOrderInLayer(int order);
    int getOrderInLayer() const;
    
    // State management
    void setState(const std::string& state);
    void addStateVisual(const std::string& state, const sf::Color& color, 
                       const std::string& animation = "");    

*/
private:
    void updateTextureRectFromAnimation();
};

#endif