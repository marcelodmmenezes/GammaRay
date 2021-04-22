#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math.hpp"
#include "ray.hpp"

class Camera
{
public:
	Camera(
		Double3 position,
		Double3 target,
		Double3 scene_up,
		double vertical_fov,
		double aspect_ratio,
		double aperture,
		double focus_dist)
	{
		double theta = degreesToRadians(vertical_fov);
		double h = tan(theta / 2.0);
		double viewport_height = 2.0 * h;
		double viewport_width = aspect_ratio * viewport_height;

		w = (position - target).normalized();
		u = cross(scene_up, w).normalized();
		v = cross(w, u);

		origin = position;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - focus_dist * w;

		lens_radius = aperture / 2.0;
	}

	Ray getRay(double s, double t) const
	{
		Double3 random = lens_radius * randomInUnitDisk();
		Double3 offset = u * random.x + v * random.y;

		return
		{
			origin + offset,
			lower_left_corner + s * horizontal + t * vertical - origin - offset
		};
	}

private:
	Double3 origin;
	Double3 lower_left_corner;
	Double3 horizontal;
	Double3 vertical;
	Double3 u, v, w;
	double lens_radius;
};

#endif // CAMERA_HPP

