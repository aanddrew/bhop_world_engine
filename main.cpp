#include "engine/engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

    bh::GameSettings settings = bh::load_default_settings();
    bh::Map map("maps/loop.obj", settings);

    sf::SoundBuffer jumpsoundbuffer;
    jumpsoundbuffer.loadFromFile("res/hup.wav");

    sf::Sound jumpsound;
    jumpsound.setBuffer(jumpsoundbuffer);

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
                if (event.key.code == sf::Keyboard::Key::F) {
                    pc.set_movement_mode((pc.get_movement_mode() == 
                                        bh::PlayerController::MODES::NOCLIP)
                                      ? bh::PlayerController::MODES::NORMAL
                                      : bh::PlayerController::MODES::NOCLIP);
                    player.set_airborne(true);
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (player.jump()) {
                    //jumpsound.play();
                }
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
        //std::cout << (pc.get_movement_mode() == bh::PlayerController::MODES::NOCLIP) << std::endl;
        
        window.clear(); 
        map.draw(player.get_camera(), window);
        if(pc.get_movement_mode() != bh::PlayerController::MODES::NOCLIP) {
            map.interact_player(player, dt.asSeconds());
        }
        window.display(); 
    } 
    return 0; 
}
