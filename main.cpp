#include "engine/engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	std::cout << "Hello, World!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800,600), "bhop_world", sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(400, 150));

    bh::Tri2 triangle(
        bh::Vec2(0.0f, 0.0f), 
        bh::Vec2(100.0f, 200.0f), 
        bh::Vec2(600.0f, 0.0f)
    );

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        bh::Tri2::draw_to_screen(triangle, window);
        window.display();
    }
	return 0;
}
