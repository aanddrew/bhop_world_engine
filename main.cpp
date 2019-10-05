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

    bh::Tri3 weird_triangle {
        bh::Vec3(0.0f, -2.0f, 7.0f),
        bh::Vec3(-12.0f, -2.0f, 12.0f),
        bh::Vec3(12.0f, -2.0f, 12.0f)
    };

    bh::Player player;
    bh::PlayerController pc(&player);

    bh::Mat3 rotation = bh::Mat3::rotation_around_y(0.000001);

    bh::Map map("map.obj");

    sf::Time dt;
    sf::Clock deltaClock;
    deltaClock.restart();
    while(window.isOpen()) {
        dt = deltaClock.restart();
        std::cout << "fps: " << 1.0/dt.asSeconds() << std::endl;
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
        
        //weird_triangle.c.z += 0.001;
        //weird_triangle.apply_transform(rotation);
        //weird_triangle.apply_transform(translation); //cam.rotate(0.000001, -0.000001); 
        bh::Tri2 projections[3]; 
        int num_triangles = bh::Camera::project_triangle(player.get_camera(), weird_triangle, projections); 
        window.clear(); 
        for(int i = 0; i < num_triangles; i++) { 
            bh::Tri2::draw_to_screen(projections[i], window); 
        } 
        map.draw(player.get_camera(), window);
        window.display(); 
    } 
    return 0; 
}
