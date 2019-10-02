#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

namespace bh {
    
class PlayerController {
public:
    PlayerController(Player* player_in);

    void KeyDown(sf::Keyboard::Key key);
    void KeyUp(sf::Keyboard::Key key);
    void MouseInput(float dx, float dy);

    void update(float dt);
private:
    Player* player;

    enum move_flags {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        JUMP,
        NUM_MOVE_FLAGS
    };

    bool moving[5];
};

}
