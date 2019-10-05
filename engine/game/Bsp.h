#pragma once

#include <memory>
#include <vector>
#include "../graphics/Tri3.h"
#include "../graphics/Tri2.h"
#include "../graphics/Camera.h"

#include <SFML/Graphics.hpp>

namespace bh {

struct node {
    Tri3 triangle;
    std::unique_ptr<node> front;
    std::unique_ptr<node> back;
};

class Bsp {
public:
    Bsp();
    Bsp(const std::vector<Tri3>& triangles);
    void draw_bsp(const Camera& camera, sf::RenderWindow& window) const;
private:
    std::unique_ptr<node> build_bsp(const std::vector<Tri3>& triangles);
    std::unique_ptr<node> head;
};

}
