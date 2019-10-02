#include "GameSettings.h"

#include <iostream>
#include <fstream>

namespace bh {

void load_settings_from_file(const std::string& file_name, GameSettings& settings) {
    std::ifstream cfg_file(file_name);
    std::string line;
    while(std::getline(cfg_file, line)) {
        std::cout << line << std::endl;
    }
}

GameSettings load_default_settings() {
    return {
        0.01,
        0.01,
        0.01,
        -0.1,
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::S,
        sf::Keyboard::Key::D,
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::Space,
    };
}

}
