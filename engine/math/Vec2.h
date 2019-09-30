#pragma once

#include <ostream>
#include <math.h>

#include <SFML/Graphics.hpp>

namespace bh {

class Vec2 {
public:
    Vec2(float, float);
    Vec2();
    
    Vec2& operator =(const Vec2& other);

    void operator +=(const Vec2& other);
    void operator -=(const Vec2& other);
    void operator *=(float scalar);
    void operator /=(float scalar);

    Vec2  operator +(const Vec2& other) const;
    Vec2  operator -(const Vec2& other) const;
    Vec2  operator *(float scalar) const;
    Vec2  operator /(float scalar) const;

    float operator[](int index);

    float magnitude();
    float magnitude_squared();
    Vec2  normalize();

    static float dot(const Vec2& first, const Vec2& second);

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec){
        os << "<" << vec.x << ", " << vec.y << ">";
        return os;
    }

    sf::Vector2f to_sfml_vector() const;

    float x, y;
};

}
