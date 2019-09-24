#pragma once

#include <ostream>
#include <math.h>

class Vec3 {
public:
    Vec3(float, float, float);
    Vec3();
    
    Vec3& operator =(const Vec3& other);

    Vec3  operator +(const Vec3& other) const;
    Vec3  operator -(const Vec3& other) const;
    Vec3  operator *(float scalar) const;
    Vec3  operator /(float scalar) const;

    float magnitude();
    float magnitude_squared();
    Vec3  normalize();

    static float  dot(const Vec3& first, const Vec3& second);
    static Vec3 cross(const Vec3& first, const Vec3& second);

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec){
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
        return os;
    }

    float x, y, z;
};

Vec3::Vec3(float x, float y, float z) {
    this-> x = x;
    this-> y = y;
    this-> z = z;
}

Vec3& Vec3::operator =(const Vec3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vec3 Vec3::operator +(const Vec3& other) const {
    return Vec3(
        x + other.x,
        y + other.y,
        z + other.z
    );
}

Vec3 Vec3::operator -(const Vec3& other) const {
    return Vec3(
        x - other.x,
        y - other.y, 
        z - other.z
    );
}

Vec3 Vec3::operator *(float scalar) const {
    return Vec3(
        x * scalar,
        y * scalar,
        z * scalar
    );
}

Vec3 Vec3::operator /(float scalar) const {
    return Vec3(
        x / scalar,
        y / scalar,
        z / scalar
    );
}

float Vec3::magnitude() {
    return sqrt(magnitude_squared());
}

float Vec3::magnitude_squared() {
    return dot(*this, *this);
}

Vec3 Vec3::normalize() {
    return *this / magnitude();
}

float Vec3::dot(const Vec3& first, const Vec3& second) {
    return first.x * second.x 
         + first.y * second.y 
         + first.z * second.z;
}

Vec3 Vec3::cross(const Vec3& first, const Vec3& second) {
    return Vec3(
        first.y * second.z - first.z * second.y,
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x
    );
}
