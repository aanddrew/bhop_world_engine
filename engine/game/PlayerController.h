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

    enum MODES {
        NOCLIP,
        NORMAL
    };

    MODES get_movement_mode() const;
    void set_movement_mode(MODES mode);

    void update(float dt);
private:
    Player* player;

    enum move_flags {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        JUMP,
        WALK,
        NUM_MOVE_FLAGS
    };

    float noclip_speed;

    MODES movement_mode;

    bool moving[5];
};

}
