#pragma once

#include "../math/Vec3.h"
#include "../graphics/Camera.h"

namespace bh {
    
//A player is a camera that moves.
class Player {
public:
    Player();
    Player(const Vec3& start_location);

    Camera& get_camera();

    void update(float dt);

    const Vec3& get_location() const;
    const Vec3& get_velocity() const;

    void accelerate(const Vec3& wishdir, float dt);
    void set_velocity(const Vec3& wishvel);
    void set_location(const Vec3& wishloc);

    void bleed_speed(float fraction);

    bool is_airborne() const;
    void set_airborne(bool new_air);

    bool is_walking() const;
    void set_walking(bool new_walk);

    float get_move_speed() const;
    void set_move_speed(float new_speed);

    bool jump();

    float get_radius() const;
private:
    Camera camera;
    Vec3 velocity;
    Vec3 acceleration;

    void ground_accelerate(const Vec3& wishdir, float dt);
    void air_accelerate(const Vec3& wishdir, float dt);

    float move_speed;

    bool airborne;
    bool walking;
};

}
