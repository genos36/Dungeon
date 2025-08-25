#include "../../include/render/AnimationSystem.h"

    AnimationSystem::Animation::Animation(const std::vector<sf::IntRect>& frames,
              AnimationID id, float frameTime, bool loop):
              frames(frames),id(id), frameTime(frameTime), loop(loop){
    }


    AnimationSystem::AnimationSystem():
        animations(std::vector<Animation>(static_cast<size_t>(AnimationID::COUNT))), currentAnimationID(AnimationID::INVALID),
        animationTimer(0.f),currentFrame(0),isPlaying(true){    }

    void AnimationSystem::addAnimation(const Animation& animation){
        if(animation.id == AnimationID::INVALID) {
            std::cerr << "Cannot add animation with INVALID ID" << std::endl;
            return;
        }
        if(static_cast<size_t>(animation.id) <animations.size()){
            animations[static_cast<size_t>(animation.id)]=animation;
        }
    }


    void AnimationSystem::addAnimation(const std::vector<sf::IntRect>& frames,
                        AnimationID id, 
                        float frameTime, 
                        bool loop ){
                            addAnimation(Animation(frames,id,frameTime,loop));
                        }


void AnimationSystem::playAnimation(AnimationID id, bool restart) {
    if(id==AnimationID::INVALID)return;
    const Animation* animation = getAnimation(id);
    if (!animation ) {
        std::cerr << "Animation not found: " << static_cast<uint32_t>(id) << std::endl;
        return;
    }
    
    // Only restart if different animation or forced
    if (currentAnimationID != id || restart) {
        currentAnimationID = id;
        currentFrame = 0;
        animationTimer = 0.0f;
        isPlaying = true;
    }
    }

    void AnimationSystem::stopAnimation(){
        isPlaying=false;
        currentAnimationID = AnimationID::INVALID;
    }


    void AnimationSystem::updateAnimation(float deltaTime) {
    if (!isPlaying||currentAnimationID==AnimationID::INVALID) return;
    
    const Animation* currentAnimation = getAnimation(currentAnimationID);
    if (!currentAnimation) {
        stopAnimation();
        return;
    }
    
    animationTimer += deltaTime;
    
    // Advance frames while we have time to account for
    while (animationTimer >= currentAnimation->frameTime && isPlaying) {
        animationTimer -= currentAnimation->frameTime;
        currentFrame++;
        
        // Check if we reached the end
        if (currentFrame >= currentAnimation->frames.size()) {
            if (currentAnimation->loop) {
                currentFrame = 0; // Loop back to start
            } else {
                // Stop at last frame
                currentFrame = currentAnimation->frames.size() - 1;
                stopAnimation();
            }
        }
    }
    }
    bool AnimationSystem::isPlayingAnimation() const {
        return isPlaying;
    }

    AnimationID AnimationSystem::getCurrentAnimationID() const {
        return currentAnimationID;
    }

    int AnimationSystem::getCurrentFrame() const {
        return currentFrame;
    }

    sf::IntRect AnimationSystem::getCurrentFrameRect() const {
    if(currentAnimationID==AnimationID::INVALID)return sf::IntRect();

    const Animation* currentAnimation = getAnimation(currentAnimationID);

    if (currentAnimation && currentFrame < currentAnimation->frames.size()) {
        return currentAnimation->frames[currentFrame];
    }
    return sf::IntRect(); // Return empty rect if no valid frame
    }

    const AnimationSystem::Animation* AnimationSystem::getAnimation(AnimationID id) const {
            if(id == AnimationID::INVALID) return nullptr;
        size_t index = static_cast<size_t>(id);
        if (index < animations.size() && !animations[index].frames.empty()) {
            if(animations[index].id==AnimationID::INVALID)return nullptr;
            return &animations[index];
        }
        return nullptr;
    }