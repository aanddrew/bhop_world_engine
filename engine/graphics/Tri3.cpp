#include "Tri3.h"

#include <iostream>

namespace bh {

Tri3::Tri3() {}

Tri3::Tri3(Vec3 a, Vec3 b, Vec3 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void Tri3::apply_transform(Mat3 transform) {
    a = transform * a;
    b = transform * b;
    c = transform * c;
}

void Tri3::apply_transform(Mat4 transform) {
    a = transform * a;
    b = transform * b;
    c = transform * c;
}

//splits a triangle along a plane, fills the returned array with the 
//3 resulting triangles.
//assumes that the plane actually intersects the triangle.
void Tri3::split_by_plane(Vec3 plane_loc, Vec3 plane_dir, Tri3* returned) const {
    //get the plane in the form of ax + by + cz = d
    float plane_a = plane_dir[0];
    float plane_b = plane_dir[1];
    float plane_c = plane_dir[2];
    float plane_d = Vec3::dot(plane_loc, plane_dir);

    //t1, t2, t3 are how far the plane intersects between:
    //ab, bc, ac respectively
    
    Vec3 ab = b - a;
    Vec3 bc = c - b;
    Vec3 ac = c - a;
    
    //ab
    float t1 = 
        (plane_d 
        - plane_a*this->a[0] 
        - plane_b*this->a[1] 
        - plane_c*this->a[2]
        )
        /
        (plane_a*ab[0] + plane_b*ab[1] + plane_c*ab[2]);
    Vec3 intersect_d = this->a + ab*t1;

    float t2 = 
        (plane_d 
        - plane_a*this->b[0] 
        - plane_b*this->b[1] 
        - plane_c*this->b[2]
        )
        /
        (plane_a*bc[0] + plane_b*bc[1] + plane_c*bc[2]);
    Vec3 intersect_e = this->b + bc*t2;

    float t3 = 
        (plane_d 
        - plane_a*this->a[0] 
        - plane_b*this->a[1] 
        - plane_c*this->a[2]
        )
        /
        (plane_a*ac[0] + plane_b*ac[1] + plane_c*ac[2]);
    Vec3 intersect_f = this->a + ac*t3;

    //d is not in triangle
    if (t1 < 0 || t1 > 1) {
        Tri3 tri_1(this->c, intersect_e, intersect_f);
        Tri3 tri_2(this->a, intersect_e, intersect_f);
        Tri3 tri_3(this->b, this->a, intersect_e);
        returned[0] = tri_1;
        returned[1] = tri_2;
        returned[2] = tri_3;
    }
    //e is not in triangle
    else if (t2 < 0 || t2 > 1) {
        Tri3 tri_1(this->a, intersect_d, intersect_f);
        Tri3 tri_2(this->b, intersect_d, intersect_f);
        Tri3 tri_3(this->c, this->b, intersect_f);
        returned[0] = tri_1;
        returned[1] = tri_2;
        returned[2] = tri_3;
    }
    //f is not in triangle
    else {
        Tri3 tri_1(this->b, intersect_d, intersect_e);
        Tri3 tri_2(this->c, intersect_d, intersect_e);
        Tri3 tri_3(this->a, this->c, intersect_d);
        returned[0] = tri_1;
        returned[1] = tri_2;
        returned[2] = tri_3;
    }
}

}
