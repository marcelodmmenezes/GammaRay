#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "material.hpp"

struct Sphere : public Hittable
{
	Double3 center;
	double radius;
	std::shared_ptr<Material> material_ptr;

	Sphere()
	{}

	Sphere(
		Double3 const& new_center,
		double new_radius,
		std::shared_ptr<Material> new_material_ptr)
		:
		center{ new_center },
		radius{ new_radius },
		material_ptr{ new_material_ptr }
	{}

	virtual bool hit(
		Ray const& r,
		double t_min,
		double t_max,
		HitRecord& record) const override
	{
		Double3 ray_origin_to_sphere_center = r.origin - center;

		double a = r.direction.normSquared();
		double half_b = dot(ray_origin_to_sphere_center, r.direction);
		double c = ray_origin_to_sphere_center.normSquared() - radius * radius;

		double discriminant = half_b * half_b - a * c;

		if (discriminant < 0.0)
		{
			return false;
		}

		double discriminant_sqrt = sqrt(discriminant);

		double root = (-half_b - discriminant_sqrt) / a;

		if (root < t_min || root > t_max)
		{
			root = (-half_b + discriminant_sqrt) / a;

			if (root < t_min || root > t_max)
			{
				return false;
			}
		}

		record.t = root;
		record.position = r.at(root);

		Double3 outward_normal = (record.position - center) / radius;
		record.setFaceNormal(r, outward_normal);

		record.material_ptr = material_ptr;

		return true;
	}
};

#endif // SPHERE_HPP

