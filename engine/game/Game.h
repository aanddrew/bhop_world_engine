#pragma once

#include "GameSettings.h"
#include "Player.h"
#include "PlayerController.h"
#include "Map.h"

#include <SFML/Graphics.hpp>

namespace bh {
    
class Game {
public:
    Game(sf::RenderWindow& window_in);
    static const GameSettings& get_settings();

    bool is_paused() const;
    void set_paused(bool paused_in);

    void update(float dt);
    void render();
private:
    Player player;
    PlayerController pc;
    Map map;

    sf::RenderWindow& window;

    static GameSettings settings;
    bool paused;
};

}
