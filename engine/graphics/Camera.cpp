#include "Camera.h"
#include "../math/Vec3.h"
#include "../math/Mat3.h"
#include "../math/Utils.h"

#include <math.h>
#include <iostream>

namespace bh {

Camera::Camera() {
    location = {0,0,0};

    forward  = {0,0,1};
    up       = {0,1,0};
    right    = {1,0,0};

    yaw = 0.0f;
    pitch = 0.0f;

    fov = 3.1415/2;
}

const Vec3& Camera::get_forward() const {
    return forward;
}

const Vec3& Camera::get_right() const {
    return right;
}

const Vec3& Camera::get_up() const {
    return up;
}

const Vec3& Camera::get_location() const {
    return location;
}

float Camera::get_pitch() const {
    return pitch;
}

float Camera::get_yaw() const {
    return yaw;
}

float Camera::get_fov() const {
    return fov;
}

float Camera::get_aspect_ratio() const {
    return aspect_ratio;
}

bool Camera::triangle_is_behind(const Camera& cam, const Tri3& triangle) {
    return point_behind_plane(cam.get_location(), cam.get_forward(), triangle.a)
        || point_behind_plane(cam.get_location(), cam.get_forward(), triangle.b)
        || point_behind_plane(cam.get_location(), cam.get_forward(), triangle.c);
}

bool Camera::project_point(const Camera& cam, const Vec3& in, Vec2* filled) {
    if (point_behind_plane(cam.get_location(), cam.get_forward(), in)) {
        return false;
    }

    Vec3 delta_point = in - cam.get_location();
    //the point using our camera's coordinate system
    Vec3 relative_point = {
        Vec3::dot(cam.right, delta_point),
        Vec3::dot(cam.up, delta_point),
        Vec3::dot(cam.forward, delta_point)
    };

    Vec2 projected = {
        relative_point.x / relative_point.z,
        relative_point.y / relative_point.z
    };
    
    *filled = projected;
    return true;
}

Camera::NumTrianglesGenerated Camera::project_triangle(const Camera& cam, const Tri3& in, Tri2* filled) {
    //first, we split the triangle according to the plane of the camera.
    std::cout << cam << std::endl;
    if (point_behind_plane(cam.get_location(), cam.get_forward(), in.a)|| point_behind_plane(cam.get_location(), cam.get_forward(), in.b) || point_behind_plane(cam.get_location(), cam.get_forward(), in.c)){
        static Tri3 splits[3]; // don't have to keep remaking this
        //have to split the triangle
        in.split_by_plane(cam.get_location() + cam.get_forward() * 0.1, cam.get_forward(), splits);
        int num_triangles_generated = 0;
        for(int i = 0; i < 3; i++) {
            std::cout << splits[i] << std::endl;
            if(!triangle_is_behind(cam, splits[i])){
                Vec2 a, b, c;
                project_point(cam, splits[i].a, &a);
                project_point(cam, splits[i].b, &b);
                project_point(cam, splits[i].c, &c);
                
                filled[num_triangles_generated] = Tri2(a, b, c);
                num_triangles_generated++;
            }
        }
        
        return static_cast<NumTrianglesGenerated>(num_triangles_generated);
    }
    else {
        Vec2 a, b, c;
        project_point(cam, in.a, &a);
        project_point(cam, in.b, &b);
        project_point(cam, in.c, &c);

        filled[0] = Tri2(a, b, c);
        return NumTrianglesGenerated::One;
    }
}

void Camera::set_rotation(float pitch, float yaw) {
    this->pitch = pitch;
    this->yaw   = yaw;

    //rotate default frame by this pitch, then this yaw
    forward = {0,0,1};
    up      = {0,1,0};
    right   = {1,0,0};

    Mat3 pitch_rotation = Mat3::rotation_around_x(pitch);
    Mat3 yaw_rotation   = Mat3::rotation_around_y(yaw);

    //pitch
    forward = pitch_rotation * forward;
    up = pitch_rotation * up;
    right = pitch_rotation * right;

    //then yaw
    forward = yaw_rotation * forward;
    up = yaw_rotation * up;
    right = yaw_rotation * right;
}

void Camera::rotate(float d_pitch, float d_yaw) {
    pitch -= d_pitch;
    yaw += d_yaw;

    set_rotation(pitch, yaw);
}

void Camera::set_location(const Vec3& new_location) {
    location = new_location;
}

void Camera::move_location(const Vec3& delta) {
    location += delta;
}
}
