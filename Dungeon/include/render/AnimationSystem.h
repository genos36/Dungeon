#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>


enum class AnimationID : uint32_t {
    INVALID = 0,
    
    // Character animations
    PLAYER_IDLE,
    PLAYER_WALK, 
    PLAYER_RUN,
    PLAYER_ATTACK,
    PLAYER_JUMP,
    
    // Enemy animations
    ENEMY_IDLE,
    ENEMY_WALK,
    ENEMY_ATTACK,
    
    // Environment animations
    TORCH_BURN,
    WATER_FLOW,
    
    COUNT // Keep last
};



class AnimationSystem{
private:

    struct Animation {
        AnimationID id;
        std::vector<sf::IntRect> frames;
        float frameTime;
        bool loop;


        Animation(const std::vector<sf::IntRect>& frames=std::vector<sf::IntRect>(),
              AnimationID id=AnimationID::INVALID, 
              float frameTime = 0.1f, 
              bool loop = false);
        };

    std::vector<Animation> animations;
    AnimationID currentAnimationID;
    float animationTimer;
    int currentFrame;
    bool isPlaying;



public:
    AnimationSystem();
    void addAnimation(const Animation& animation);
    void addAnimation(const std::vector<sf::IntRect>& frames,
                        AnimationID id=AnimationID::INVALID, 
                        float frameTime = 0.1f, 
                        bool loop = true);
    void playAnimation(AnimationID id=AnimationID::INVALID, bool restart = false);
    void stopAnimation();
    void updateAnimation(float deltaTime);
    bool isPlayingAnimation() const;

    AnimationID getCurrentAnimationID() const;
    int getCurrentFrame() const ;
    sf::IntRect getCurrentFrameRect() const;
    const Animation* getAnimation(AnimationID id) const;
};

#endif