#include "camera.hpp"
#include "hittableList.hpp"
#include "material.hpp"
#include "math.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "util.hpp"
#include "writer.hpp"

#include <iostream>

Double3 rayColor(Ray const& r, Hittable const& scene, int depth)
{
	if (depth <= 0)
	{
		return Double3{ 0.0, 0.0, 0.0 };
	}

	HitRecord record;

	if (scene.hit(r, 0.001, INF, record))
	{
		Ray scattered;
		Double3 attenuation;

		if (record.material_ptr->scatter(r, record, attenuation, scattered))
		{
			return attenuation * rayColor(scattered, scene, depth - 1);
		}

		return Double3(0.0, 0.0, 0.0);
	}

	double t = 0.5 * (r.direction.normalized().y + 1.0);

	return (1.0 - t) * Double3(1.0, 1.0, 1.0) + t * Double3(0.5, 0.7, 1.0);
}

void generateScene(HittableList& scene)
{
	auto material_ground = std::make_shared<Lambertian>(Double3{ 0.5, 0.5, 0.5 });
	scene.add(std::make_shared<Sphere>(Double3(0.0, -1000.0, 0.0), 1000, material_ground));

	for (int i = -11; i < 11; ++i)
	{
		for (int j = -11; j < 11; ++j)
		{
			double material_prob = randomDouble();

			Double3 center
			{
				i + 0.9 * randomDouble(),
				0.2,
				j + 0.9 * randomDouble()
			};

			if ((center - Double3{ 4.0, 0.2, 0.0 }).norm() > 0.9)
			{
				std::shared_ptr<Material> material_sphere;

				if (material_prob < 0.8)
				{
					Double3 albedo = Double3::random() * Double3::random();
					material_sphere = std::make_shared<Lambertian>(albedo);
				}
				else if (material_prob < 0.95)
				{
					Double3 f_0 = Double3::random(0.5, 1.0);
					double roughness = randomDouble(0.0, 0.5);
					material_sphere = std::make_shared<Metal>(f_0, roughness);
				}
				else
				{
					material_sphere = std::make_shared<Dielectric>(1.5);
				}

				scene.add(std::make_shared<Sphere>(center, 0.2, material_sphere));
			}
		}
	}

	auto material_1 = std::make_shared<Dielectric>(1.5);
	auto material_2 = std::make_shared<Lambertian>(Double3{ 0.4, 0.2, 0.1 });
	auto material_3 = std::make_shared<Metal>(Double3{ 0.7, 0.6, 0.5 }, 0.0);

	scene.add(std::make_shared<Sphere>(Double3{ 0.0, 1.0, 0.0 }, 1.0, material_1));
	scene.add(std::make_shared<Sphere>(Double3{ -4.0, 1.0, 0.0 }, 1.0, material_2));
	scene.add(std::make_shared<Sphere>(Double3{ 4.0, 1.0, 0.0 }, 1.0, material_3));
}

int main()
{
	/// IMAGE
	double const aspect_ratio = 3.0 / 2.0;
	int const image_width = 1200;
	int const image_height = static_cast<int>(image_width / aspect_ratio);
	int const n_samples_per_pixel = 500;
	int const max_depth = 50;

	/// SCENE
	HittableList scene;
	generateScene(scene);

	/// CAMERA
	Double3 camera_position{ 13.0, 2.0, 3.0 };
	Double3 camera_target{ 0.0, 0.0, 0.0 };
	Double3 scene_up{ 0.0, 1.0, 0.0 };
	double dist_to_focus = 10.0;
	double aperture = 0.1;

	Camera camera(
		camera_position,
		camera_target,
		scene_up,
		20.0,
		aspect_ratio,
		aperture,
		dist_to_focus);

	/// RENDERING
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "Row #" << j << std::endl;

		for (int i = 0; i < image_width; ++i)
		{
			Double3 pixel(0.0, 0.0, 0.0);

			for (int k = 0; k < n_samples_per_pixel; ++k)
			{
				double u = (i + randomDouble()) / (image_width - 1);
				double v = (j + randomDouble()) / (image_height - 1);

				pixel += rayColor(camera.getRay(u, v), scene, max_depth);
			}

			writeColor(std::cout, pixel, n_samples_per_pixel);
		}
	}

	std::cerr << "\nDONE\n";
}

