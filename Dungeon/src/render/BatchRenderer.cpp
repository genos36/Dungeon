#include "../../include/render/BatchRenderer.h"


BatchRenderer::BatchRenderer(sf::RenderWindow* window):window(window),vertexArray(sf::Quads),currentTex(nullptr){}

void BatchRenderer::begin(){
    vertexArray.clear();
    currentTex = nullptr;
}

void BatchRenderer::addSprite(const sf::Sprite& sprite){
    const sf::Texture* texture=sprite.getTexture();
    if(!texture)return;

    if(texture!=currentTex){
        flush();
    }
    currentTex =texture;
    addSpriteVertices(sprite);
}

void BatchRenderer::end() {
    if (vertexArray.getVertexCount()!=0) {
        flush();
    }
}

void BatchRenderer::flush(){
    sf::RenderStates states;
    states.texture=currentTex;
    window->draw(vertexArray,states);
    vertexArray.clear();
    currentTex=nullptr;
}


void BatchRenderer::addSpriteVertices(const sf::Sprite& sprite){
    sf::Vector2f position=sprite.getPosition();
    sf::IntRect texRect=sprite.getTextureRect();
    sf::Color color=sprite.getColor();

    sf::Vertex vertices[4];

    // Position vertices (forming a rectangle)
    vertices[0].position = position;
    vertices[1].position = position + sf::Vector2f(texRect.width, 0);
    vertices[2].position = position + sf::Vector2f(texRect.width, texRect.height);
    vertices[3].position = position + sf::Vector2f(0, texRect.height);


        // Texture coordinates (which part of texture to use)
    vertices[0].texCoords = sf::Vector2f(texRect.left, texRect.top);
    vertices[1].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top);
    vertices[2].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top + texRect.height);
    vertices[3].texCoords = sf::Vector2f(texRect.left, texRect.top + texRect.height);
  
    // Color (for tinting)
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;

    // Add to vertex array
    for (int i = 0; i < 4; i++) {
        this->vertexArray.append(vertices[i]);
    }
}


BatchRenderer::~BatchRenderer(){
    end(); // Ensure any partial batch gets drawn
}