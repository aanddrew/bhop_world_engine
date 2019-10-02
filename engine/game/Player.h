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

    void accelerate(const Vec3& wishdir, float dt);
    void set_velocity(const Vec3& wishvel);
private:
    Camera camera;
    Vec3 velocity;
    Vec3 acceleration;

    bool is_airborne;
};

}
