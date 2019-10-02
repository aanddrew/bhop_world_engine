#include "Player.h"

namespace bh {

Player::Player() 
: Player({0,0,0})
{}

Player::Player(const Vec3& start_location)
: camera(start_location)
{
    is_airborne = false;
}

void Player::update(float dt) {
    velocity += acceleration;
    camera.move_location(velocity);
}

void Player::accelerate(const Vec3& wishdir, float dt) {
    static const float MOVE_SPEED = 0.003;
    velocity += wishdir * dt * MOVE_SPEED;
}

void Player::set_velocity(const Vec3& wishvel) {
    velocity = wishvel;
}

Camera& Player::get_camera() {
    return camera;
}

    
}
