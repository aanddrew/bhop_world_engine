#pragma once

#include <vector>
#include "Tri3.h"

namespace bh {

class Mesh {
public:
    Mesh(const std::string& file_name);
    void draw() const;
private:
    std::vector<Tri3> triangles;
};

}
