#include "PlayerController.h"

#include <iostream>

#include "Game.h"
#include "GameSettings.h"

namespace bh {
    
PlayerController::PlayerController(Player* player_in) 
: player(player_in)
{
    for(int i = 0; i < NUM_MOVE_FLAGS; i++) {
        moving[i] = false;
    }
}

void PlayerController::KeyDown(sf::Keyboard::Key key) {
    if (key == Game::get_settings().forward_key){
        moving[FORWARD] = true;
    }
    else if (key == Game::get_settings().backward_key) {
        moving[BACKWARD] = true;
    }
    else if (key == Game::get_settings().left_key) {
        moving[LEFT] = true;
    }
    else if(key == Game::get_settings().right_key) {
        moving[RIGHT] = true;
    }
}

void PlayerController::KeyUp(sf::Keyboard::Key key) {
    if (key == Game::get_settings().forward_key){
        moving[FORWARD] = false;
    }
    else if (key == Game::get_settings().backward_key) {
        moving[BACKWARD] = false;
    }
    else if (key == Game::get_settings().left_key) {
        moving[LEFT] = false;
    }
    else if(key == Game::get_settings().right_key) {
        moving[RIGHT] = false;
    }
}

void PlayerController::MouseInput(float dx, float dy) {
    player->get_camera().rotate(dx, dy);
}

void PlayerController::update(float dt) {
    Vec3 wishdir(0,0,0);
    if (moving[RIGHT]){
        wishdir += player->get_camera().get_right();
    }
    if (moving[LEFT]){
        wishdir -= player->get_camera().get_right();
    }
    if (moving[FORWARD]){
        wishdir += player->get_camera().get_forward();
    }
    if (moving[BACKWARD]){
        wishdir -= player->get_camera().get_forward();
    }

    //now normalize it to the x/z plane
    //player->accelerate(wishdir, dt);
    player->set_velocity(wishdir * 0.001);
    player->update(dt);
}

}
