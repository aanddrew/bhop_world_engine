#include "PlayerController.h"

#include <iostream>

namespace bh {
    
PlayerController::PlayerController(Player* player_in) 
: player(player_in)
{
    for(int i = 0; i < NUM_MOVE_FLAGS; i++) {
        moving[i] = false;
    }
}

void PlayerController::KeyDown(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Key::W:
            moving[FORWARD] = true;
            break;
        case sf::Keyboard::Key::A:
            moving[LEFT] = true;
            break;
        case sf::Keyboard::Key::S:
            moving[BACKWARD] = true;
            break;
        case sf::Keyboard::Key::D:
            moving[RIGHT] = true;
            break;
    }
}

void PlayerController::KeyUp(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Key::W:
            moving[FORWARD] = false;
            break;
        case sf::Keyboard::Key::A:
            moving[LEFT] = false;
            break;
        case sf::Keyboard::Key::S:
            moving[BACKWARD] = false;
            break;
        case sf::Keyboard::Key::D:
            moving[RIGHT] = false;
            break;
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
