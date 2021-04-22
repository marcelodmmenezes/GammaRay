#include "camera.hpp"
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
	int const n_samples_per_pixel = 100;

	/// SCENE
	HittableList scene;
	scene.add(std::make_shared<Sphere>(Double3(0.0, 0.0, -1.0), 0.5));
	scene.add(std::make_shared<Sphere>(Double3(0.0, -100.5, -1.0), 100.0));

	/// CAMERA
	Camera camera(aspect_ratio);

	/// RENDERING
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < image_width; ++i)
		{
			Double3 pixel(0.0, 0.0, 0.0);

			for (int k = 0; k < n_samples_per_pixel; ++k)
			{
				double u = (i + randomDouble()) / (image_width - 1);
				double v = (j + randomDouble()) / (image_height - 1);

				pixel += rayColor(camera.getRay(u, v), scene);
			}

			writeColor(std::cout, pixel, n_samples_per_pixel);
		}
	}
}

