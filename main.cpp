#include "engine/engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280,720), "bhop_world", sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(400, 150));

    bh::Tri2 triangle(
        bh::Vec2(0.0f, 0.0f), 
        bh::Vec2(100.0f, 200.0f), 
        bh::Vec2(600.0f, 0.0f)
    );

    bh::Player player;
    bh::PlayerController pc(&player);

    bh::Mat3 rotation = bh::Mat3::rotation_around_y(0.000001);

    bh::Map map("maps/intersect.obj");

    sf::Time dt;
    sf::Clock deltaClock;
    deltaClock.restart();
    while(window.isOpen()) {
        dt = deltaClock.restart();
        //std::cout << "fps: " << 1.0/dt.asSeconds() << std::endl;
        bh::Mat4 translation = bh::Mat4::translate(0.7*dt.asSeconds(), 0, 0);

        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                pc.KeyDown(event.key.code);
            }
            if (event.type == sf::Event::KeyReleased) {
                pc.KeyUp(event.key.code);
            }
        }

        pc.update(dt.asSeconds());

        float dx = sf::Mouse::getPosition(window).x - window.getView().getSize().x/2;
        float dy = sf::Mouse::getPosition(window).y - window.getView().getSize().y/2;
        pc.MouseInput(dy * -0.005, dx * 0.005);
        if (dx != 0 || dy  != 0)
            sf::Mouse::setPosition(sf::Vector2i(window.getView().getSize().x/2,window.getView().getSize().y/2), window);
        //hide that mouse cursor
        window.setMouseCursorVisible(false);

        //std::cout << player.get_camera().get_location() << std::endl;
        
        window.clear(); 
        map.draw(player.get_camera(), window);
        window.display(); 
    } 
    return 0; 
}
