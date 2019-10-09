#include "Player.h"

#include <iostream>

namespace bh {

Player::Player() 
: Player({0,0,0})
{}

Player::Player(const Vec3& start_location)
: camera(start_location)
{
    airborne = false;
}

void Player::update(float dt) {
    velocity += acceleration * dt;
    camera.move_location(velocity * dt);
}

void Player::accelerate(const Vec3& wishdir, float dt) {
    static const float MOVE_SPEED = 50;
    static const float MAX_FORWARD_SPEED = 40;
    float forward_speed = Vec3::dot(velocity, wishdir);
    float addspeed = MAX_FORWARD_SPEED - forward_speed;
    
    velocity += wishdir * dt * addspeed;
    std::cout << velocity.magnitude() << std::endl;
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

bool Player::is_airborne() const {
    return airborne;
}

void Player::set_airborne(bool new_air) {
    airborne = new_air;
}

bool Player::jump() {
    if(!airborne) {
        set_airborne(true);
        velocity += Vec3(0, 7, 0);
        return true;
    }
    return false;
}
    
}
