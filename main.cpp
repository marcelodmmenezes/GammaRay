#include "hittableList.hpp"
#include "math.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "util.hpp"

#include <iostream>

Double3 rayColor(Ray const& r, HittableList const& scene)
{
	HitRecord rec;

	if (scene.hit(r, 0, INF, rec))
	{
		return 0.5 * (rec.normal + Double3(1.0, 1.0, 1.0));
	}

	double t = 0.5 * (r.direction.normalized().y + 1.0);

	return (1.0 - t) * Double3(1.0, 1.0, 1.0) + t * Double3(0.5, 0.7, 1.0);
}

int main()
{
	/// IMAGE
	double const aspect_ratio = 16.0 / 9.0;
	int const image_width = 400;
	int const image_height = static_cast<int>(image_width / aspect_ratio);

	/// SCENE
	HittableList scene;
	scene.add(std::make_shared<Sphere>(Double3(0.0, 0.0, -1.0), 0.5));
	scene.add(std::make_shared<Sphere>(Double3(0.0, -100.5, -1.0), 100.0));

	/// CAMERA
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	Double3 origin(0.0, 0.0, 0.0);
	Double3 horizontal(viewport_width, 0.0, 0.0);
	Double3 vertical(0.0, viewport_height, 0.0);

	Double3 lower_left_corner =
		origin - horizontal / 2.0 - vertical / 2.0 -
		Double3(0.0, 0.0, focal_length);

	/// RENDERING
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < image_width; ++i)
		{
			double u = static_cast<double>(i) / (image_width - 1);
			double v = static_cast<double>(j) / (image_height - 1);

			Ray r
			{
				origin,
				lower_left_corner + u * horizontal + v * vertical - origin
			};

			Double3 pixel = rayColor(r, scene);
			writeColor(std::cout, pixel);
		}
	}
}

