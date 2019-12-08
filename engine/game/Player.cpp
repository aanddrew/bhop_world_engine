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
    float speed_now = move_speed;
    if (walking)
        speed_now *= 0.5;

    velocity += wishdir * speed_now * 10 * dt;
    float mag_velocity = velocity.magnitude();
    if (mag_velocity > speed_now) {
        velocity = velocity * (speed_now/mag_velocity);
    }
    //apply ground friction
    float friction = speed_now*0.5 * dt;
    velocity = velocity - (velocity * friction);
}

//code literally copied directly from source sdk
void Player::air_accelerate(const Vec3& wishdir, float dt) {
    float accel = 800;
    float currentspeed = velocity.magnitude();
    float addspeed = 0.1;
    float accelspeed = 0.1;
	float wishspd = 1;

    float air_speed_cap = 70.0f;

	// Cap speed
	if ( wishspd > air_speed_cap )
		wishspd = air_speed_cap;

	// Determine veer amount
    currentspeed = Vec3::dot(velocity, wishdir);

	// See how much to add
	addspeed = wishspd - currentspeed;

	// If not adding any, done.
	if (addspeed <= 0)
		return;

	// Determine acceleration speed after acceleration
	accelspeed = accel * wishspd * dt;

	// Cap it
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	
	// Adjust pmove vel.
    velocity += wishdir * accelspeed;
}
    
}

