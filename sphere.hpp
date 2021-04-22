#ifndef SPHERE_HPP
#define SPHERE_HPP

struct Sphere : public Hittable
{
	Double3 center;
	double radius;

	Sphere()
	{}

	Sphere(Double3 const& new_center, double new_radius)
		: center{ new_center }, radius{ new_radius }
	{}

	virtual bool hit(
		Ray const& r,
		double t_min,
		double t_max,
		HitRecord& record) const override
	{
		Double3 oc = r.origin - center;

		double a = r.direction.normSquared();
		double half_b = dot(oc, r.direction);
		double c = oc.normSquared() - radius * radius;

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

		return true;
	}
};

#endif // SPHERE_HPP

