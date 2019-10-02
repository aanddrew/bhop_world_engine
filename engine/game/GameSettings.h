#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct GameSettings {
    float MAX_SPEED;
    float AIR_ACCELERATION;
    float GROUND_ACCELERATION;
    float GRAVITY;

    sf::Keyboard::Key FORWARD_KEY;
    sf::Keyboard::Key BACKWARD_KEY;
    sf::Keyboard::Key RIGHT_KEY;
    sf::Keyboard::Key LEFT_KEY;
    sf::Keyboard::Key JUMP_KEY;
};

void load_settings_from_file(const std::string& file_name, GameSettings& settings);
