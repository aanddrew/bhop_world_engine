#pragma once

#include "../math/Vec3.h"
#include "../math/Mat3.h"
#include "../math/Mat4.h"

namespace bh {

class Tri3 {
public:
    Tri3(Vec3 a, Vec3 b, Vec3 c);

    void apply_transform(Mat3 transform);
    void apply_transform(Mat4 transform);

    void split_by_plane(Vec3 plane_loc, Vec3 plane_dir, Tri3* returned);

    Vec3 a, b, c;
private:
};

}
