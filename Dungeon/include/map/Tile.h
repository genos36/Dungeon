#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile{
    private:
        bool isWalkable;
        bool isExit;
        sf::Sprite sprite;
        sf::Vector2f position;

    public:

        // static constexpr float SIDE_LENGHT=30.0f;
        // Tile(float x, float y, bool isWalkable=true, bool isExit=false);
};

#endif


