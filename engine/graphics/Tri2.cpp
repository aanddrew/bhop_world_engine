#include "Tri2.h"

#include <iostream>

namespace bh {
    
Tri2::Tri2(Vec2 a, Vec2 b, Vec2 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void Tri2::draw_to_screen(const Tri2& triangle, sf::RenderWindow& window)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(3);
    static sf::Color color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    polygon.setFillColor(color);

    Vec2 a = triangle.a;
    Vec2 b = triangle.b;
    Vec2 c = triangle.c;

    unsigned int half_width = window.getSize().x / 2;
    unsigned int half_height= window.getSize().y / 2;

    //std::cout << "width: " << half_width << std::endl;
    //std::cout << "height: " << half_height << std::endl;

    a.x *= half_width;
    b.x *= half_width;
    c.x *= half_width;

    a.y *= (half_height * -1.0f);
    b.y *= (half_height * -1.0f);
    c.y *= (half_height * -1.0f);

    bh::Vec2 window_center(half_width, half_height);
    a += window_center;
    b += window_center;
    c += window_center;
    
    /*
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    */

    polygon.setPoint(0, a.to_sfml_vector());
    polygon.setPoint(1, b.to_sfml_vector());
    polygon.setPoint(2, c.to_sfml_vector());
    window.draw(polygon);
}

}
