#pragma once

#include "../math/Vec3.h"
#include "../math/Vec2.h"

class Camera {
public:
	Camera();
	Camera(const Vec3& location);

	const Vec3& get_forward() const;
	const Vec3& get_right() const;
	const Vec3& get_up() const;

	const Vec3& get_location() const;

	float get_pitch() const;
	float get_yaw() const;

	float get_fov() const;
	float get_aspect_ratio() const;

	//yaw and pitch in radians
	void set_rotation(float pitch, float yaw);
	void rotate(float d_pitch, float d_yaw);

	static Vec2 project_point(const Camera& cam, const Vec3& in);

private:
	Vec3 forward, right, up;
	Vec3 location;//location or position?
	float yaw, pitch;

	float fov;
	float aspect_ratio;
};
