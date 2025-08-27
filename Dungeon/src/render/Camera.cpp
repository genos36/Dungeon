#include "../../include/render/Camera.h"

float Camera::randomFloat(float min,float max){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen); 
}


Camera::Camera(const sf::Vector2f& center,const sf::Vector2f& size):
    view(center,size),targetPosition(center),
    zoomLevel(INITIAL_ZOOM_LEVEL),targetZoomLevel(INITIAL_ZOOM_LEVEL),
    moveSpeed(INITIAL_MOVE_SPEED),zoomSpeed(INITIAL_ZOOM_SPEED),
    boundsMin(),boundsMax(),
    useBounds(false),
    shakeAmount(INITIAL_SHAKE_AMOUNT), shakeDuration(INITIAL_SHAKE_DURATION),
    shakeTimer(INITIAL_SHAKE_TIMER)
    {}

// Smoothly interpolates camera position/zoom toward targets each frame
void Camera::update(float deltaTime){
    sf::Vector2f currentCenter = view.getCenter();
    sf::Vector2f direction= targetPosition-currentCenter;

    float distance=std::sqrt(direction.x*direction.x+direction.y*direction.y);

    if(distance>0.1f){
        sf::Vector2f newCenter = currentCenter+direction*moveSpeed*deltaTime;
        view.setCenter(newCenter);
    }
    else{
        view.setCenter(targetPosition);
    }

    //Zoom
    float zoomDiff=targetZoomLevel-zoomLevel;

    if(std::abs(zoomDiff)>0.01f){
        float currentZoom=zoomLevel;
        zoomLevel+=zoomDiff*zoomSpeed*deltaTime;
        view.zoom(zoomLevel/currentZoom);
    }
    // Update screen shake
    updateShake(deltaTime);

    if(useBounds){
        clampToBounds();
    }

}

//  Applies camera view to render window with shake offset
void Camera::applyToWindow(sf::RenderWindow& window){
    sf::View shakenView=view;
    shakenView.move(shakeOffset);
    window.setView(shakenView);

}


// Sets where camera should smoothly move to
void Camera::setTargetPosition(const sf::Vector2f& targetPosition){
    this->targetPosition=targetPosition;
    if(useBounds){
        clampToBounds();
    }
}

//  Instantly jumps camera to position (for cutscenes)
void Camera::setPositionImmediate(const sf::Vector2f& position){
    targetPosition=position;
    view.setCenter(position);
    if(useBounds){
        clampToBounds();
    }
}

//  Offsets target position relative to current position
void Camera::move(const sf::Vector2f& offset){
    targetPosition +=offset;

    if(useBounds){
        clampToBounds();
    }
}
// Get camera's destination position
const  sf::Vector2f& Camera::getTargetPosition() const{
return targetPosition;
}
// Get camera's current position
const  sf::Vector2f& Camera::getCurrentPosition() const{
return view.getCenter();
}



// Sets target zoom level for smooth interpolation
void Camera::setZoom(float zoom){
    targetZoomLevel = std::max(0.1f, std::min(4.f,zoom)); // Prevent zooming too close or too far
}

// Instantly sets zoom (no smoothing)
void Camera::setZoomImmediate(float zoom){
    setZoom(zoom);
    view.zoom(zoom/zoomLevel);
    zoomLevel=zoom;
}

// Relative zoom multiplier
void Camera::zoom(float factor) {
    setZoom(targetZoomLevel * factor);
}

// Returns current target zoom level
float Camera::getZoom()const{
    return targetZoomLevel;
}

// Controls interpolation speed for position
void Camera::setMoveSpeed(float speed){
    moveSpeed=std::max(0.1f, std::min(4.f,speed));
}
// Controls interpolation speed for zoom
void Camera::setZoomSpeed(float speed){
    zoomSpeed=std::max(0.1f, std::min(4.f,speed));
}

// Confines camera to specified world area
void Camera::setBounds(const sf::Vector2f& min, const sf::Vector2f& max){
    boundsMin.emplace(min);
    boundsMax.emplace(max);
    useBounds=true;
    clampToBounds();
}

// Removes camera movement restrictions
void Camera::clearBounds(){
    useBounds=false;
    boundsMin.reset();
    boundsMax.reset();
}

// Checks if position is within camera bounds
bool Camera::isInBounds(const sf::Vector2f& position) const{
        if (!useBounds ||!boundsMin.has_value()||!boundsMax.has_value()) return true;
            return position.x >= boundsMin->x && position.x <= boundsMax->x &&
                   position.y >= boundsMin->y && position.y <= boundsMax->y;
}


// Starts screen shake effect with intensity/duration
void Camera::shake(float amount, float duration ){
    shakeAmount=amount;
    shakeDuration=duration;
    shakeTimer=0.f;
}

// Immediately stops any active shaking
void Camera::stopShake(){
    shakeAmount=0.f;
    shakeDuration=0.f;
    shakeTimer=0.f;
    shakeOffset=sf::Vector2f(0.f,0.f);
}   


// Converts screen pixels to world coordinates
sf::Vector2f Camera::screenToWorld(const sf::Vector2f& screenPos,const sf::RenderWindow& window)const{
    return window.mapPixelToCoords(sf::Vector2i(screenPos), view);
}

//  Converts world coordinates to screen pixels
sf::Vector2f Camera::worldToScreen(const sf::Vector2f& worldPos,const sf::RenderWindow& window)const{
    return sf::Vector2f(window.mapCoordsToPixel(worldPos, view));
}

// Returns current SFML view for rendering
const sf::View& Camera::getView()const{
    return view;
}

//  Returns visible world area as rectangle
const sf::FloatRect Camera::getViewBounds()const{
    auto center=view.getCenter();
    auto size=view.getSize();

    return sf::FloatRect(center.x - size.x / 2, center.y - size.y / 2, 
        size.x, size.y);
}

// Checks if object is within camera view
bool Camera::isPointVisible(const sf::Vector2f& worldPos) const {
    sf::FloatRect bounds = getViewBounds();
    return bounds.contains(worldPos);
}
// Checks if object is within camera view
bool Camera::isRectVisible(const sf::FloatRect& worldRect) const {
    sf::FloatRect viewBounds = getViewBounds();
    return viewBounds.intersects(worldRect);
}

// Directional movement
void Camera::moveUp(float speedMultiplier) {
    move(sf::Vector2f(0, -moveSpeed * speedMultiplier));
}

void Camera::moveDown(float speedMultiplier) {
    move(sf::Vector2f(0, moveSpeed * speedMultiplier));
}

void Camera::moveLeft(float speedMultiplier) {
    move(sf::Vector2f(-moveSpeed * speedMultiplier, 0));
}

void Camera::moveRight(float speedMultiplier) {
    move(sf::Vector2f(moveSpeed * speedMultiplier, 0));
}

// Zoom convenience
void Camera::zoomIn(float factor) {
    setZoom(targetZoomLevel / factor); // Division for zoom in
}

void Camera::zoomOut(float factor) {
    setZoom(targetZoomLevel * factor); // Multiplication for zoom out
}

void Camera::resetZoom() {
    setZoom(INITIAL_ZOOM_LEVEL);
}

// // Advanced movement
// void Camera::followEntity(const Entity& entity, float offsetX, float offsetY) {
//     setTargetPosition(entity.getPosition() + sf::Vector2f(offsetX, offsetY));
// }

void Camera::centerOnPosition(const sf::Vector2f& position) {
    setPositionImmediate(position);
}

// // Smooth panning (would need additional state tracking)
// void Camera::panToPosition(const sf::Vector2f& position, float duration) {
//     // Implementation would store pan target and duration
//     // then interpolate in update() method
// }




// Private methods
void Camera::updateShake(float deltaTime) {
    if (shakeTimer < shakeDuration) {
        shakeTimer += deltaTime;
        shakeOffset = calculateShakeOffset();
    } else {
        shakeOffset = sf::Vector2f(0, 0);
    }
}

sf::Vector2f Camera::calculateShakeOffset() const {
    if (shakeAmount <= 0.0f) return sf::Vector2f(0, 0);
    
    float progress = shakeTimer / shakeDuration;
    float intensity = shakeAmount * (1.0f - progress); // Fade out
    
    return sf::Vector2f(
        randomFloat(-intensity, intensity),
        randomFloat(-intensity, intensity)
    );
}

void Camera::clampToBounds() {
    if (!useBounds) return;
    
    sf::Vector2f size = view.getSize();
    sf::Vector2f halfSize = size / 2.0f;
    
    // Clamp target position
    targetPosition.x = std::max(boundsMin->x + halfSize.x, std::min(boundsMax->x - halfSize.x, targetPosition.x));
    targetPosition.y = std::max(boundsMin->y + halfSize.y, std::min(boundsMax->y - halfSize.y, targetPosition.y));
    
    // Also clamp current position immediately
    sf::Vector2f currentCenter = view.getCenter();
    currentCenter.x = std::max(boundsMin->x + halfSize.x, std::min(boundsMax->x - halfSize.x, currentCenter.x));
    currentCenter.y = std::max(boundsMin->y + halfSize.y, std::min(boundsMax->y - halfSize.y, currentCenter.y));
    view.setCenter(currentCenter);
}

float Camera::getMoveSpeed()const{
    return moveSpeed;
}
float Camera::getZoomSpeed()const{
    return zoomSpeed;
}
