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
    velocity += acceleration * dt;
    camera.move_location(velocity * dt);
}

void Player::accelerate(const Vec3& wishdir, float dt) {
    static const float MOVE_SPEED = 0.003;
    velocity += wishdir * dt * MOVE_SPEED;
}

void Player::set_velocity(const Vec3& wishvel) {
    velocity = wishvel;
}
void Player::set_location(const Vec3& wishloc) {
    camera.set_location(wishloc);
}

Camera& Player::get_camera() {
    return camera;
}

const Vec3& Player::get_location() const {
    return camera.get_location();
}

const Vec3& Player::get_velocity() const {
    return velocity;
}

float Player::get_radius() const {
    return 2.0f;
}
    
}
