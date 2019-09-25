#pragma once

#include "Vec3.h"

class Mat3{
public:
    Mat3(const Vec3& first, const Vec3& second, const Vec3& third);

    const Vec3& operator[](int index) const;
    Vec3 operator*(const Vec3& other);

    static Mat3 identity();

    static Mat3 rotation_around_x(float theta); //positive rotates up
    static Mat3 rotation_around_y(float theta); //positive rotates right
    static Mat3 rotation_around_z(float theta); //dont use for camera (roll)

    friend std::ostream& operator<<(std::ostream& os, const Mat3& mat){
        os << "|" << mat[0] << "|" << std::endl 
           << "|" << mat[1] << "|" << std::endl 
           << "|" << mat[2] << "|";
        return os;
    }


private:
    Vec3 first, second, third;
};
