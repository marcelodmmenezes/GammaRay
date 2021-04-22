#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"

#include <memory>

struct Material;

struct HitRecord
{
	Double3 position;
	Double3 normal;
	std::shared_ptr<Material> material_ptr;

	double t;
	bool front_face;

	inline void setFaceNormal(Ray const& r, Double3 const& outward_normal)
	{
		front_face = dot(r.direction, outward_normal) < 0.0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

struct Hittable
{
	virtual bool hit(
		Ray const& r,
		double t_min,
		double t_max,
		HitRecord& record) const = 0;
};

#endif // HITTABLE_HPP

