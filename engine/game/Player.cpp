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
    move_speed = 15.0f;
}

void Player::update(float dt) {
    velocity += acceleration * dt;
    camera.move_location(velocity * dt);
}

void Player::accelerate(const Vec3& wishdir, float dt) {
    if (airborne) {
        air_accelerate(wishdir, dt);
    }
    else {
        ground_accelerate(wishdir, dt);
    }
        
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

bool Player::is_walking() const {
    return walking;
}

void Player::set_walking(bool new_walk) {
    walking = new_walk;
}

bool Player::jump() {
    if(!airborne) {
        set_airborne(true);
        velocity += Vec3(0, 7, 0);
        return true;
    }
    return false;
}

float Player::get_move_speed() const {
    return move_speed;
}

void Player::set_move_speed(float new_speed) {
    move_speed = new_speed;
}

void Player::ground_accelerate(const Vec3& wishdir, float dt) {
    velocity += wishdir * move_speed * dt;
    float mag_velocity = velocity.magnitude();
    if (mag_velocity > move_speed) {
        mag_velocity *= move_speed/mag_velocity;
    }
}

void Player::air_accelerate(const Vec3& wishdir, float dt) {
    float accelerate = 100;
    float proj_vel = Vec3::dot(velocity, wishdir);
    float accel_vel = accelerate * dt;

    float angle_cos = Vec3::dot(velocity.normalize(), wishdir);

    if (proj_vel + accel_vel > move_speed) {
        accel_vel = move_speed - proj_vel;
    }
    Vec3 add_vec;
    if (angle_cos < 0) {
        add_vec = wishdir * (accel_vel * (1 - angle_cos));
    }
    else {
        add_vec = wishdir * accel_vel;
    }
    velocity += add_vec;
}
    
}

