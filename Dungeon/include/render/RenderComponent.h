#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#pragma once
#include <SFML/Graphics.hpp>
#include "TextureRegistry.h"
#include "LayeredRenderSystem.h"

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
    sf::Shader* shader;
    sf::BlendMode blendMode;
    int orderInLayer;
    
    // Animation system
    struct Animation {
        std::vector<sf::IntRect> frames;
        float frameTime;
        bool loop;
        std::string name;
    };
    
    std::map<std::string, Animation> animations;
    Animation* currentAnimation;
    float animationTimer;
    int currentFrame;
    
    // State system
    std::map<std::string, std::pair<sf::Color, std::string>> stateVisuals;
    std::string currentState;
    
    // Helper methods
    sf::Color applyOpacity(const sf::Color& baseColor) const;
    void updateTextureRectFromAnimation();

public:
    RenderComponent(TextureType);




};

#endif