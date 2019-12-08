#include "engine/engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280,720), "bhop_world", sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(400, 150));

    bh::Game game(window);

    float dt;
    sf::Clock deltaClock;
    deltaClock.restart();
    while(window.isOpen()) {
        dt = deltaClock.restart().asSeconds();
        //std::cout << "fps: " << 1.0/dt.asSeconds() << std::endl;
        if (!game.is_paused()) {
            game.update(dt);
            window.clear();
            game.render();
            window.display();
        }
        else {
            window.close();
        }
    } 
    return 0; 
}
