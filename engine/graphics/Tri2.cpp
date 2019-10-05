#include "Tri2.h"

#include <iostream>

namespace bh {

Tri2::Tri2() {}
    
Tri2::Tri2(Vec2 a, Vec2 b, Vec2 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void Tri2::draw_to_screen(const Tri2& triangle, sf::RenderWindow& window)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(3);
    polygon.setFillColor(triangle.color);

    Vec2 a = triangle.a;
    Vec2 b = triangle.b;
    Vec2 c = triangle.c;

    unsigned int half_width = window.getSize().x / 2;
    unsigned int half_height= window.getSize().y / 2;
    float aspect_ratio = half_width * 1.0 / half_height * 1.0;

    a.x *= half_width / aspect_ratio;
    b.x *= half_width / aspect_ratio;
    c.x *= half_width / aspect_ratio;

    a.y *= (half_height * -1.0f);
    b.y *= (half_height * -1.0f);
    c.y *= (half_height * -1.0f);

    bh::Vec2 window_center(half_width, half_height);
    a += window_center;
    b += window_center;
    c += window_center;

    polygon.setPoint(0, a.to_sfml_vector());
    polygon.setPoint(1, b.to_sfml_vector());
    polygon.setPoint(2, c.to_sfml_vector());
    window.draw(polygon);
}

void Tri2::set_color(const sf::Color& color) {
    this->color = color;
}

}
