#include "Game.h"

namespace bh {

GameSettings Game::settings = load_default_settings();

Game::Game(sf::RenderWindow& window_in) 
: window(window_in),
  player(),
  pc(&player),
  map("maps/starter.obj", settings)
{
    paused = true;
}

const GameSettings& Game::get_settings() {
    return settings;
}

bool Game::is_paused() const {
    return paused;
}

void Game::set_paused(bool paused_in) {
    paused = paused_in;
}

void Game::update(float dt) {
    sf::Event event;
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            pc.KeyDown(event.key.code);
            //pausing
            if (event.key.code == sf::Keyboard::Key::Escape) {
                window.setMouseCursorVisible(true);
                paused = true;
                return;
            }
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

    pc.update(dt);

    float dx = sf::Mouse::getPosition(window).x - window.getView().getSize().x/2;
    float dy = sf::Mouse::getPosition(window).y - window.getView().getSize().y/2;
    pc.MouseInput(dy * -0.005, dx * 0.005);
    if (dx != 0 || dy  != 0)
        sf::Mouse::setPosition(sf::Vector2i(window.getView().getSize().x/2,window.getView().getSize().y/2), window);
    //hide that mouse cursor
    window.setMouseCursorVisible(false);

    if(pc.get_movement_mode() != bh::PlayerController::MODES::NOCLIP) {
        map.interact_player(player, dt);
    }
}

void Game::render() {
    map.draw(player.get_camera(), window);
}

}
