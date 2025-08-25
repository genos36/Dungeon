#include "../include/render/RenderSystem.h"
#include "../include/render/LayeredRenderSystem.h"
#include "../include/render/TextureRegistry.h"
#include "../include/render/TextureLoader.h"
#include "../include/render/AnimationSystem.h"
#include "../include/render/RenderComponent.h"
int main() {

    /*
    sf::RenderWindow window(sf::VideoMode(800, 600), "Render System Demo");
    RenderSystem renderSystem(&window);
    

    
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Rendering
        renderSystem.beginFrame();
        
        // Draw some tiles
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                TextureType tileType = (x + y) % 2 == 0 ? 
                    TextureType::TILE_GRASS : TextureType::TILE_STONE;
                
                renderSystem.drawTile(tileType, sf::Vector2f(x * 32.0f, y * 32.0f));
            }
        }
        
        // Draw a player
        renderSystem.drawSprite(TextureType::TILE_ROCK, sf::Vector2f(300, 200));
        
        renderSystem.endFrame();
    }

    
    
    // Cleanup
    TextureLoader::instance()->cleanup();
    */


    sf::RenderWindow window(sf::VideoMode(800, 600), "Render System Demo");
    LayeredRenderSystem renderSystem(&window);
    TextureLoader* textureLoader=TextureLoader::instance();

    RenderComponent RedTree(TextureType::TREE, RenderLayer::ENTITIES);
    RedTree.setColor(sf::Color::Red);
    RenderComponent blueTree(TextureType::TREE, RenderLayer::ENTITIES);
    blueTree.setColor(sf::Color::Blue);




// Play animation

// Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Rendering
        renderSystem.beginFrame();
        
        sf::Sprite grass(*(textureLoader->loadTexture(TextureType::TILE_GRASS))),
                    rock(*(textureLoader->loadTexture(TextureType::TILE_ROCK))),
                    tree(*(textureLoader->loadTexture(TextureType::TREE)));


        // Draw some tiles
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                (x+y)%2>0?grass.setPosition(x*32,y*32):
                            rock.setPosition(x*32,y*32);                
                (x+y)%2>0?renderSystem.addToLayer(RenderLayer::BACKGROUND,grass):
                            renderSystem.addToLayer(RenderLayer::BACKGROUND,rock);
                tree.setPosition(x*32,y*32);
                
                if((x+y)%2)renderSystem.addToLayer(RenderLayer::BACKGROUND,RedTree.createSprite(sf::Vector2f( x*32,y*32)));
                else renderSystem.addToLayer(RenderLayer::BACKGROUND,blueTree.createSprite(sf::Vector2f( x*32,y*32)));

            }
        }


        
        renderSystem.renderAll();
        // treeRender.draw(window,sf::Vector2f(0.f,0.f));
        renderSystem.endFrame();
    }









    return 0;
}