#pragma once

#include "Vec3.h"

namespace bh {

bool point_behind_plane(const Vec3& plane_loc, const Vec3& plane_dir, const Vec3& point);

}
