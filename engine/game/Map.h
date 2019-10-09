#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../graphics/Tri3.h"
#include "../physics/PhysTri3.h"
#include "../graphics/Camera.h"
#include "GameSettings.h"
#include "Bsp.h"

namespace bh {
 
class Map {
public:
    Map(const std::string& file_name, const GameSettings& settings);

    void draw(const Camera& camera, sf::RenderWindow& window) const;
    void interact_player(Player& player, float dt) const;
private:
    void collide_player(Player& player, float dt) const;
    void apply_gravity_player(Player& player, float dt) const;

    std::vector<Tri3> triangles;
    std::vector<PhysTri3> phys_triangles;
    Bsp bsp;

    const GameSettings * settings;
};

}
