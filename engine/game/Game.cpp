#include "Game.h"

namespace bh {

Game::Game() 
{
    load_settings_from_file("config/default.cfg", this->settings);
}

}
