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
    movement_mode = NOCLIP;
    noclip_speed = 50.0f;
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
    else if (key == Game::get_settings().jump_key) {
        moving[JUMP] = true;
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
    else if(key == Game::get_settings().jump_key) {
        moving[JUMP] = false;
    }
}

void PlayerController::MouseInput(float dx, float dy) {
    player->get_camera().rotate(dx, dy);
}

void PlayerController::update(float dt) {
    switch(movement_mode) {
        case NOCLIP: {
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
            player->set_velocity(wishdir * noclip_speed);
            player->update(dt);
        }
        break;
        case NORMAL: {
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

            if (moving[JUMP] && !player->is_airborne()) {
                player->jump();
            }
    
            Vec3 wishdir_xz(wishdir.x, 0, wishdir.z);
            //now normalize it to the x/z plane
            player->accelerate(wishdir_xz.normalize(), dt);
            player->update(dt);

        }
        break;
    }
}

PlayerController::MODES PlayerController::get_movement_mode() const {
    return movement_mode;
}

void PlayerController::set_movement_mode(MODES mode) {
    movement_mode = mode;
}

}
