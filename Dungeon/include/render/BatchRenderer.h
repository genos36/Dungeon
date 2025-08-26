#ifndef BATCHRENDERER_H
#define BATCHRENDERER_H

#include <SFML/Graphics.hpp>
#include <memory>

class BatchRenderer{
    private:
    sf::RenderWindow* window;
    sf::VertexArray vertexArray;
    const sf::Texture*  currentTex;

    public:

    BatchRenderer(sf::RenderWindow* window);
    ~BatchRenderer();
    void begin();
    void addSprite(const sf::Sprite& sprite);
    void flush();
    void end();
    
    private:
    void addSpriteVertices(const sf::Sprite& sprite);
};

#endif