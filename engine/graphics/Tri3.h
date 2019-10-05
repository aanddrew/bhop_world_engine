#pragma once

#include "../math/Vec3.h"
#include "../math/Mat3.h"
#include "../math/Mat4.h"

#include <SFML/Graphics.hpp>

namespace bh {

class Tri3 {
public:
    Tri3();
    Tri3(Vec3 a, Vec3 b, Vec3 c);

    void apply_transform(Mat3 transform);
    void apply_transform(Mat4 transform);

    void split_by_plane(Vec3 plane_loc, Vec3 plane_dir, Tri3* returned) const;

    friend std::ostream& operator<<(std::ostream& os, const Tri3& tri){
        os << "Tri3:" << std::endl
           << "\ta: " << tri.a << std::endl
           << "\tb: " << tri.b << std::endl
           << "\tc: " << tri.c << std::endl;
        return os;
    }

    Vec3 a, b, c;
    sf::Color color;
private:
};

}
