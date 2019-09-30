#pragma once

#include "Vec3.h"
#include "Vec4.h"

namespace bh {

class Mat4{
public:
    Mat4(const Vec4& first, const Vec4& second, const Vec4& third, const Vec4& fourth);

    const Vec4& operator[](int index) const;
    Vec4 operator*(const Vec4& other);
    Vec3 operator*(const Vec3& other);

    static Mat4 identity();

    static Mat4 rotation_around_x(float theta); //positive rotates up
    static Mat4 rotation_around_y(float theta); //positive rotates right
    static Mat4 rotation_around_z(float theta); //dont use for camera (roll)

    static Mat4 translate(float x, float y, float z);

    friend std::ostream& operator<<(std::ostream& os, const Mat4& mat){
        os << "|" << mat[0] << "|" << std::endl 
           << "|" << mat[1] << "|" << std::endl 
           << "|" << mat[2] << "|" << std::endl
           << "|" << mat[3] << "|";
        return os;
    }


private:
    Vec4 first, second, third, fourth;
};

}
