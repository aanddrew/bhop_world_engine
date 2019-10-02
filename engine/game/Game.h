#pragma once

#include "GameSettings.h"
#include "Player.h"

namespace bh {
    
class Game {
public:
    Game();
    static const GameSettings& get_settings();
private:
    Player player;
    static GameSettings settings;
};

}
