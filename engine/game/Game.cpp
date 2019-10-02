#include "Game.h"

namespace bh {

GameSettings Game::settings = load_default_settings();

Game::Game() 
{

}

const GameSettings& Game::get_settings() {
    return settings;
}

}
