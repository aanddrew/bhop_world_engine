#include "Mat4.h"
#include <math.h>

namespace bh {

Mat4::Mat4(const Vec4& first, const Vec4& second, const Vec4& third, const Vec4& fourth) {
    this->first = first;
    this->second = second;
    this->third = third;
    this->fourth = fourth;
}

const Vec4& Mat4::operator[](int index) const {
    switch(index) {
        case 0: return first; break;
        case 1: return second; break;
        case 2: return third; break;
        case 3: return fourth; break;
    }
    throw std::invalid_argument("Matrix index out of bounds");
}

Vec4 Mat4::operator*(const Vec4& other) {
    return {
        Vec4::dot(first, other),
        Vec4::dot(second, other),
        Vec4::dot(third, other),
        Vec4::dot(fourth, other)
    };
}

Mat4 Mat4::identity() {
    return {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
}

//each of these rotates a vector counter-clockwise when the axis of rotation is 
//pointing towards the observer.

Mat4 Mat4::rotation_around_x(float theta) {
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    return {
        {1,         0,            0,0},
        {0, cos_theta, -1*sin_theta,0},
        {0, sin_theta,    cos_theta,0},
        {0,         0,            0,1}
    };
}

Mat4 Mat4::rotation_around_y(float theta) {
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    return {
        {   cos_theta, 0, sin_theta,0},
        {           0, 1, 0        ,0},
        {-1*sin_theta, 0, cos_theta,0},
        {           0, 0,         0,1}
    };
}

Mat4 Mat4::rotation_around_z(float theta) {
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    return {
        {cos_theta, -1*sin_theta, 0,0},
        {sin_theta,    cos_theta, 0,0},
        {        0,            0, 1,0},
        {           0, 0,         0,1}
    };
}

Mat4 Mat4::translate(float x, float y, float z) {
    return {
        {1,0,0,x},
        {0,1,0,y},
        {0,0,1,z},
        {0,0,0,1}
    };
}

}
