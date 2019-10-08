#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../graphics/Tri3.h"
#include "../physics/PhysTri3.h"
#include "../graphics/Camera.h"
#include "Bsp.h"

namespace bh {
    
class Map {
public:
    Map(const std::string& file_name);

    void draw(const Camera& camera, sf::RenderWindow& window) const;
    void collide_player(Player& player, float dt) const;
private:
    std::vector<Tri3> triangles;
    std::vector<PhysTri3> phys_triangles;
    Bsp bsp;
};

}
