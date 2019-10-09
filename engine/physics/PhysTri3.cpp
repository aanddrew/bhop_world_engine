#include "PhysTri3.h"

#include <iostream>

namespace bh {

PhysTri3::PhysTri3(Vec3 a, Vec3 b, Vec3 c, Vec3 n) 
: Tri3(a, b, c, n)
{
    Vec3 center_of_triangle = (a + b + c)/3;
    Vec3 norm_ab_hypothetical = Vec3::cross((b-a), n).normalize();
    Vec3 norm_bc_hypothetical = Vec3::cross((c-b), n).normalize();
    Vec3 norm_ac_hypothetical = Vec3::cross((c-a), n).normalize();

    norm_ab = (Vec3::dot(norm_ab_hypothetical, (center_of_triangle - a)) > 0) 
            ? norm_ab_hypothetical 
            : norm_ab_hypothetical * -1;
    norm_bc = (Vec3::dot(norm_bc_hypothetical, (center_of_triangle - b)) > 0) 
            ? norm_bc_hypothetical 
            : norm_bc_hypothetical * -1;
    norm_ac = (Vec3::dot(norm_ac_hypothetical, (center_of_triangle - a)) > 0) 
            ? norm_ac_hypothetical 
            : norm_ac_hypothetical * -1;

    static const float ONE_OVER_SQUARE_ROOT_TWO = 0.70711;
    i_am_a_floor = (Vec3::dot(normal, Vec3(0,1,0)) > ONE_OVER_SQUARE_ROOT_TWO);
}

PhysTri3::PhysTri3(const Tri3& triangle)
: PhysTri3(triangle.a, triangle.b, triangle.c, triangle.normal)
{}

bool PhysTri3::collide_player(Player& player, float dt) const {
    Vec3 next_location = player.get_location() + player.get_velocity() * dt;
    Vec3 al = next_location - a;
    Vec3 bl = next_location - b;
    Vec3 cl = next_location - c;
    float dist_to_ab = Vec3::dot(norm_ab, al);
    float dist_to_bc = Vec3::dot(norm_bc, bl);
    float dist_to_ac = Vec3::dot(norm_ac, cl);
    float dist_to_plane = Vec3::dot(normal, al);
    if (dist_to_plane < player.get_radius() 
        && dist_to_plane > 0
        && dist_to_ab > 0
        && dist_to_bc > 0
        && dist_to_ac > 0) {
        //correct collision
        float dr = player.get_radius() - dist_to_plane;
        player.set_velocity(player.get_velocity() - normal * Vec3::dot(player.get_velocity(), normal));
        if (this->is_floor()) {
            player.set_velocity(player.get_velocity() * 0.99);
            player.set_airborne(false);
        }
        player.set_location(next_location + normal * dr);
        return true;
    }
    return false;
}

bool PhysTri3::is_floor() const {
    return i_am_a_floor;
}

}
