#pragma once

#include "../graphics/Tri3.h"
#include "../math/Vec3.h"
#include "../game/Player.h"

namespace bh {

class PhysTri3 : public Tri3 {
public:
    PhysTri3(Vec3 a, Vec3 b, Vec3 c, Vec3 n);
    PhysTri3(const Tri3& triangle);

    //bool is_sphere_colliding(const Vec3& location, float radius) const;
    bool collide_player(Player& player, float dt) const;
    bool is_floor() const;
private:
    Vec3 norm_ab, norm_bc, norm_ac;
    bool i_am_a_floor;
};
    
}
