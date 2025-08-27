#include "../include/render/RenderSystem.h"
#include "../include/render/LayeredRenderSystem.h"
#include "../include/render/TextureRegistry.h"
#include "../include/render/TextureLoader.h"
#include "../include/render/AnimationSystem.h"
#include "../include/render/Camera.h"
#include "../include/render/RenderComponent.h"
#include "../include/render/BatchRenderer.h"
#include "../include/render/BatchRenderLayerSystem.h"
#include "render/CulledRenderSystem.h"
#include "render/CullingStrategy/AbstractCullingStrategy.h"
#include "render/CullingStrategy/ConservativeFrustumCulling.h"
#include "render/CullingStrategy/DistanceCullingStrategy.h"
#include "render/CullingStrategy/ZoomAwareCullingStrategy.h"
#include "render/CullingStrategy/NoCullingStrategy.h"
void test1(){
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
}


void test2(){

sf::RenderWindow window(sf::VideoMode(800, 600), "Render System Demo");
TextureLoader* textureLoader = TextureLoader::instance();

// Create camera centered on world origin (0,0) looking at 800x600 area
Camera camera(sf::Vector2f(400, 300), sf::Vector2f(800, 600)); // Center on (400,300), view size 800x600
BatchRenderLayerSystem renderSystem(&window);
// Game loop
while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
            
        // Add camera movement for testing
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Left: camera.move(sf::Vector2f(-50, 0)); break;
                case sf::Keyboard::Right: camera.move(sf::Vector2f(50, 0)); break;
                case sf::Keyboard::Up: camera.move(sf::Vector2f(0, -50)); break;
                case sf::Keyboard::Down: camera.move(sf::Vector2f(0, 50)); break;
                case sf::Keyboard::Q: camera.zoom(0.8f); break; // Zoom in
                case sf::Keyboard::E: camera.zoom(1.2f); break; // Zoom out
            }
        }
    }
    
    float deltaTime = 0.016f; // ~60 FPS
    camera.update(deltaTime);
    
    // Rendering
    renderSystem.beginFrame();
    
    // APPLY CAMERA TO WINDOW FIRST - this is crucial!
    camera.applyToWindow(window);
    
    // Create sprites once (more efficient)
    sf::Sprite grass(*(textureLoader->loadTexture(TextureType::TILE_GRASS)));
    sf::Sprite rock(*(textureLoader->loadTexture(TextureType::TILE_ROCK)));
    
    RenderComponent RedTree(TextureType::TREE, RenderLayer::ENTITIES);
    RedTree.setColor(sf::Color::Red);
    RenderComponent BlueTree(TextureType::TREE, RenderLayer::ENTITIES); 
    BlueTree.setColor(sf::Color::Blue);

    // Draw tiles - use WORLD coordinates, not screen coordinates!
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            sf::Vector2f worldPosition(x * 32, y * 32); // World coordinates
            
            if ((x + y) % 2 > 0) {
                grass.setPosition(worldPosition); // World coordinates!
                renderSystem.addToLayer(RenderLayer::BACKGROUND, grass);
            } else {
                rock.setPosition(worldPosition); // World coordinates!
                renderSystem.addToLayer(RenderLayer::BACKGROUND, rock);
            }
            
            // Add trees - also use world coordinates
            if ((x + y) % 2) {
                renderSystem.addToLayer(RenderLayer::ENTITIES, 
                    RedTree.createSprite(worldPosition));
            } else {
                renderSystem.addToLayer(RenderLayer::ENTITIES,
                    BlueTree.createSprite(worldPosition));
            }
        }
    }
    
    renderSystem.renderAll();
    renderSystem.endFrame();
}




}

void test3(){

sf::RenderWindow window(sf::VideoMode(800, 600), "Render System Demo");
// LayeredRenderSystem renderSystem(&window);
BatchRenderer batchRenderer(&window);
BatchRenderLayerSystem renderSys(&window);
TextureLoader* textureLoader = TextureLoader::instance();

// Create camera centered on world origin (0,0) looking at 800x600 area
Camera camera(sf::Vector2f(400, 300), sf::Vector2f(800, 600)); // Center on (400,300), view size 800x600

// Game loop
while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
            
        // Add camera movement for testing
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Left: camera.moveLeft(); break;
                case sf::Keyboard::Right: camera.moveRight(); break;
                case sf::Keyboard::Up: camera.moveUp(); break;
                case sf::Keyboard::Down: camera.moveDown(); break;
                case sf::Keyboard::Q: camera.zoom(0.8f); break; // Zoom in
                case sf::Keyboard::E: camera.zoom(1.2f); break; // Zoom out
            }
        }
    }
    
    float deltaTime = 0.016f; // ~60 FPS
    camera.update(deltaTime);
    
    // Rendering
    renderSys.beginFrame();

    
    // APPLY CAMERA TO WINDOW FIRST - this is crucial!
    camera.applyToWindow(window);
    
    // Create sprites once (more efficient)
    sf::Sprite grass(*(textureLoader->loadTexture(TextureType::TILE_GRASS)));
    sf::Sprite rock(*(textureLoader->loadTexture(TextureType::TILE_ROCK)));
    
    RenderComponent RedTree(TextureType::TREE, RenderLayer::ENTITIES);
    RedTree.setColor(sf::Color::Red);
    RenderComponent BlueTree(TextureType::TREE, RenderLayer::ENTITIES); 
    BlueTree.setColor(sf::Color::Blue);

    // Draw tiles - use WORLD coordinates, not screen coordinates!
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            sf::Vector2f worldPosition(x * 32, y * 32); // World coordinates
            
            if ((x + y) % 2 > 0) {
                grass.setPosition(worldPosition); // World coordinates!
                renderSys.addToLayer(RenderLayer::BACKGROUND,grass);
            } else {
                rock.setPosition(worldPosition); // World coordinates!
                renderSys.addToLayer(RenderLayer::BACKGROUND,rock);
            }
            
            // Add trees - also use world coordinates
            if ((x + y) % 2) {
                renderSys.addToLayer(RenderLayer::ENTITIES,RedTree.createSprite(worldPosition));
            } else {
                renderSys.addToLayer(RenderLayer::ENTITIES,BlueTree.createSprite(worldPosition));
            }
        }
    }
    


    renderSys.renderAll();

    renderSys.endFrame();
}  
}






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
// LayeredRenderSystem renderSystem(&window);
BatchRenderer batchRenderer(&window);
TextureLoader* textureLoader = TextureLoader::instance();

// Create camera centered on world origin (0,0) looking at 800x600 area
Camera camera(sf::Vector2f(400, 300), sf::Vector2f(800, 600)); // Center on (400,300), view size 800x600
CulledRenderSystem renderSys(&window);
renderSys.setCamera(&camera);

renderSys.setCullingStrategy(std::make_unique<ZoomAwareCullingStrategy>(ZoomAwareCullingStrategy()));
// Game loop
while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
            
        // Add camera movement for testing
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Left: camera.moveLeft(); break;
                case sf::Keyboard::Right: camera.moveRight(); break;
                case sf::Keyboard::Up: camera.moveUp(); break;
                case sf::Keyboard::Down: camera.moveDown(); break;
                case sf::Keyboard::Q: camera.zoom(0.8f); break; // Zoom in
                case sf::Keyboard::E: camera.zoom(1.2f); break; // Zoom out
            }
        }
    }
    
    float deltaTime = 0.016f; // ~60 FPS
    camera.update(deltaTime);
    
    // Rendering
    renderSys.beginFrame();

    
    // APPLY CAMERA TO WINDOW FIRST - this is crucial!
    camera.applyToWindow(window);
    
    // Create sprites once (more efficient)
    sf::Sprite grass(*(textureLoader->loadTexture(TextureType::TILE_GRASS)));
    sf::Sprite rock(*(textureLoader->loadTexture(TextureType::TILE_ROCK)));
    
    RenderComponent RedTree(TextureType::TREE, RenderLayer::ENTITIES);
    RedTree.setColor(sf::Color::Red);
    RenderComponent BlueTree(TextureType::TREE, RenderLayer::ENTITIES); 
    BlueTree.setColor(sf::Color::Blue);

    // Draw tiles - use WORLD coordinates, not screen coordinates!
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            sf::Vector2f worldPosition(x * 32, y * 32); // World coordinates
            
            if ((x + y) % 2 > 0) {
                grass.setPosition(worldPosition); // World coordinates!
                renderSys.addToLayer(RenderLayer::BACKGROUND,grass);
            } else {
                rock.setPosition(worldPosition); // World coordinates!
                renderSys.addToLayer(RenderLayer::BACKGROUND,rock);
            }
            
            // Add trees - also use world coordinates
            if ((x + y) % 2) {
                renderSys.addToLayer(RenderLayer::ENTITIES,RedTree.createSprite(worldPosition));
            } else {
                renderSys.addToLayer(RenderLayer::ENTITIES,BlueTree.createSprite(worldPosition));
            }
        }
    }
    


    renderSys.renderAll();

    renderSys.endFrame();
}







    return 0;
}


