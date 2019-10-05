#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../graphics/Tri3.h"
#include "../graphics/Camera.h"

namespace bh {
    
class Map {
public:
    Map(const std::string& file_name);

    void draw(const Camera& camera, sf::RenderWindow& window) const;
private:
    std::vector<Tri3> triangles;
};

}
