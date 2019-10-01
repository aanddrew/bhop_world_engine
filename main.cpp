#include "engine/engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "bhop_world", sf::Style::Titlebar);
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

    bh::Camera cam;

    bh::Mat3 rotation = bh::Mat3::rotation_around_y(0.000001);

    sf::Time dt;
    sf::Clock deltaClock;
    deltaClock.restart();
    while(window.isOpen()) {
        dt = deltaClock.restart();
        bh::Mat4 translation = bh::Mat4::translate(0.7*dt.asSeconds(), 0, 0);

        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
				switch(event.key.code)
				{
					case sf::Keyboard::Key::Right:
				        cam.rotate(0, 0.1);
					break;
                    case sf::Keyboard::Key::Left:
				        cam.rotate(0, -0.1);
					break;
                    case sf::Keyboard::Key::Up:
				        cam.rotate(0.1, 0);
					break;
                    case sf::Keyboard::Key::Down:
				        cam.rotate(-0.1, 0);
					break;
                    case sf::Keyboard::Key::W:
                        cam.move_location(cam.get_forward() * 0.1);
                    break;
                    case sf::Keyboard::Key::A:
                        cam.move_location(cam.get_right() * -0.1);
                    break;
                    case sf::Keyboard::Key::S:
                        cam.move_location(cam.get_forward() * -0.1);
                    break;
                    case sf::Keyboard::Key::D:
                        cam.move_location(cam.get_right() * 0.1);
                    break;
                }
            }
        }
        
        //weird_triangle.c.z += 0.001;
        //weird_triangle.apply_transform(rotation);
        //weird_triangle.apply_transform(translation);
        //cam.rotate(0.000001, -0.000001);
        bh::Tri2 projections[3];
        int num_triangles = bh::Camera::project_triangle(cam, weird_triangle, projections);

        window.clear();
        for(int i = 0; i < num_triangles; i++) {
            bh::Tri2::draw_to_screen(projections[i], window);
        }
        window.display();
    }
	return 0;
}
