/*
    main.cpp
    Norepinephrine

    This file starts the entire game.
*/

#include "player.h"
#include "menu.h"
#include <iostream>

int main() { 
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Norepinephrine", sf::Style::Fullscreen);

    //window.setFramerateLimit(60); // Used to limit frames per second.

    // Set window icon
    sf::Image icon; icon.loadFromFile("resources/textures/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Set game background
    sf::Texture background;
    background.loadFromFile("resources/textures/backdrophd.png");
    sf::Sprite backdrop(background);
    backdrop.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    backdrop.setOrigin(background.getSize().x / 2, background.getSize().y / 2);

    // Create platform
    sf::Texture platform;
    platform.loadFromFile("resources/textures/platform.png");
    sf::Sprite platformS(platform);
    platformS.setPosition(0.0, window.getSize().y - platform.getSize().y);

    // Create player
    Player player(window, "resources/textures/jaskier.png", platformS);
    player.place(sf::Vector2u(100, (platformS.getPosition().y - player.getBounds().height) + 25.0f));
    
    // Start clock for delta time calculations.
    static sf::Clock clock;
    float delta = 0.0f;

    bool mainMenu = true;

    Menu menu{window};

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }


        delta = clock.restart().asSeconds();

        // Clear last frame
        window.clear();

        
        menu.draw();
   
        // Render game
        window.draw(backdrop);
        window.draw(platformS);
        player.update(delta);
        //player2.update(delta);
        window.display();
    }

    return 0;
}