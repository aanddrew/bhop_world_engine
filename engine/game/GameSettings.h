#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace bh {

struct GameSettings {
    float max_speed;
    float air_acceleration;
    float ground_acceleration;
    float gravity;

    sf::Keyboard::Key forward_key;
    sf::Keyboard::Key backward_key;
    sf::Keyboard::Key right_key;
    sf::Keyboard::Key left_key;
    sf::Keyboard::Key jump_key;
};

void load_settings_from_file(const std::string& file_name, GameSettings& settings);

GameSettings load_default_settings();

}
