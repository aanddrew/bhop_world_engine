#pragma once

#include "GameSettings.h"
#include "Player.h"

namespace bh {
    
class Game {
public:
    Game();
private:
    Player player;
    GameSettings settings;
};

}
