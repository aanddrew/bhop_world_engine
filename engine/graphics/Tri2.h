#pragma once

#include <SFML/Graphics.hpp>

#include "../math/Vec2.h"

namespace bh {

class Tri2 {
public:
    Tri2();
    Tri2(Vec2 a, Vec2 b, Vec2 c);

    static void draw_to_screen(const Tri2& triangle, sf::RenderWindow& window);

    friend std::ostream& operator<<(std::ostream& os, const Tri2& tri){
        os << "Tri2:" << std::endl
           << "\ta: " << tri.a << std::endl
           << "\tb: " << tri.b << std::endl
           << "\tc: " << tri.c << std::endl;
        return os;
    }

    Vec2 a, b, c;
private:
};

}
