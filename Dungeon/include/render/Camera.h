#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <optional>





class Camera{
private:

//basic implementation
    sf::View view;
    sf::Vector2f targetPosition;
    float zoomLevel;
    float targetZoomLevel;
    float moveSpeed;

//enhanced implementation
    float zoomSpeed;
    std::optional<sf::Vector2f> boundsMin;      // World bounds (optional)
    std::optional<sf::Vector2f> boundsMax;      // World bounds (optional)
    bool useBounds;              // Whether to use bounds checking
    float shakeAmount;           // For screen shake effects
    float shakeDuration;         // How long shake lasts
    float shakeTimer;            // Current shake time
    sf::Vector2f shakeOffset;    // Current shake offset

    
    // Simple random number generator for screen shake
    static float randomFloat(float min, float max);

    //static configuration variable
    static constexpr float INITIAL_ZOOM_LEVEL=1.f;
    static constexpr float INITIAL_MOVE_SPEED=10.f;
    static constexpr float INITIAL_ZOOM_SPEED=1.f;
    static constexpr float INITIAL_SHAKE_AMOUNT=0.f;
    static constexpr float INITIAL_SHAKE_DURATION=1.f;
    static constexpr float INITIAL_SHAKE_TIMER=1.f;


public:
    //constructor
    Camera(const sf::Vector2f& center,const sf::Vector2f& size);
    
    //core methods
    void update(float deltaTime);
    void applyToWindow(sf::RenderWindow& window) ;
    
    //Position control
    void setTargetPosition(const sf::Vector2f& targetPosition);
    void setPositionImmediate(const sf::Vector2f& position);
    void move(const sf::Vector2f& offset);
    const sf::Vector2f& getTargetPosition() const;
    const sf::Vector2f& getCurrentPosition() const;
    
    //zoom control
    void setZoom(float zoom);
    void setZoomImmediate(float zoom);
    void zoom(float factor);
    float getZoom()const;

    //movement settings
    void setMoveSpeed(float speed);
    void setZoomSpeed(float speed);

    // World bounds
    void setBounds(const sf::Vector2f& min, const sf::Vector2f& max);
    void clearBounds();
    bool isInBounds(const sf::Vector2f& position) const;

    // Screen shake
    void shake(float amount, float duration = 0.5f);
    void stopShake();    

    // Coordinate conversion
    sf::Vector2f screenToWorld(const sf::Vector2f& screenPos,const sf::RenderWindow& window)const;
    sf::Vector2f worldToScreen(const sf::Vector2f& worldPos,const sf::RenderWindow& window)const;
    
    // View access   
    const sf::View& getView()const;
    const sf::FloatRect getViewBounds()const;

    // Utility
    bool isPointVisible(const sf::Vector2f& worldPos) const;
    bool isRectVisible(const sf::FloatRect& worldRect) const;
    // Directional movement methods
    void moveUp(float speedMultiplier=1.f);
    void moveDown(float speedMultiplier=1.f);
    void moveLeft(float speedMultiplier=1.f);
    void moveRight(float speedMultiplier=1.f);
    // Zoom convenience methods
    void zoomIn(float factor=1.2f);
    void zoomOut(float factor=0.8f);
    void resetZoom();                   // Reset to default zoom level

    // Preset movement methods  
    // void followEntity(const Entity& entity, float offsetX = 0.0f, float offsetY = 0.0f);
    // void panToPosition(const sf::Vector2f& position, float duration = 1.0f);
    void centerOnPosition(const sf::Vector2f& position);

private:
    void updateShake(float deltaTime);
    sf::Vector2f calculateShakeOffset() const;
    void clampToBounds();

};


#endif