#include "Utils.h"

namespace bh {

bool point_behind_plane(const Vec3& plane_loc, const Vec3& plane_dir, const Vec3& point) {
    return Vec3::dot(plane_dir, (point - plane_loc)) <= 0;
}

}
