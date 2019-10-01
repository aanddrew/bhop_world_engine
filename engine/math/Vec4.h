#pragma once

#include <ostream>
#include <math.h>

#include "Vec3.h"

namespace bh {

class Vec4 {
public:
    Vec4(float, float, float, float);
    Vec4(const Vec3& other, float);
    Vec4(const Vec3& other);
    Vec4();
    
    Vec4& operator =(const Vec4& other);
    Vec4& operator =(const Vec3& other);

    void operator +=(const Vec4& other);
    void operator -=(const Vec4& other);
    void operator *=(float scalar);
    void operator /=(float scalar);

    Vec4  operator +(const Vec4& other) const;
    Vec4  operator -(const Vec4& other) const;
    Vec4  operator *(float scalar) const;
    Vec4  operator /(float scalar) const;
    
    float operator[](int index) const;

    float magnitude();
    float magnitude_squared();
    Vec4  normalize();

    static float dot(const Vec4& first, const Vec4& second);

    friend std::ostream& operator<<(std::ostream& os, const Vec4& vec){
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
        return os;
    }

    float x, y, z, w;
};

}
