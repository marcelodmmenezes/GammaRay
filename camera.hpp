#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math.hpp"
#include "ray.hpp"

class Camera
{
public:
	Camera(double aspect_ratio)
	{
		double viewport_height = 2.0;
		double viewport_width = aspect_ratio * viewport_height;
		double focal_length = 1.0;

		origin = Double3(0.0, 0.0, 0.0);
		horizontal = Double3(viewport_width, 0.0, 0.0);
		vertical = Double3(0.0, viewport_height, 0.0);

		lower_left_corner =
			origin - horizontal / 2.0 - vertical / 2.0 -
			Double3(0.0, 0.0, focal_length);
	}

	Ray getRay(double u, double v) const
	{
		return
		{
			origin,
			lower_left_corner + u * horizontal + v * vertical - origin
		};
	}

private:
	Double3 origin;
	Double3 lower_left_corner;
	Double3 horizontal;
	Double3 vertical;
};

#endif // CAMERA_HPP

