#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "ray.hpp"
#include "util.hpp"

struct Material
{
	virtual bool scatter(
		Ray const& incoming_ray,
		HitRecord const& record,
		Double3& attenuation,
		Ray& scattered_ray) const = 0;
};

struct Lambertian : public Material
{
	Double3 albedo;

	Lambertian(Double3 const& new_albedo) : albedo{ new_albedo } {}

	virtual bool scatter(
		Ray const& incoming_ray,
		HitRecord const& record,
		Double3& attenuation,
		Ray& scattered_ray) const override
	{
		Double3 scatter_direction = record.normal + randomUnitDouble3();

		// Degenerate direction
		if (scatter_direction.nearZero())
		{
			scatter_direction = record.normal;
		}

		scattered_ray = Ray{ record.position, scatter_direction };

		attenuation = albedo;

		return true;
	}
};

struct Metal : public Material
{
	Double3 f_0;
	double roughness;

	Metal(Double3 const& new_f_0, double roughness)
		:
		f_0{ new_f_0 },
		roughness{roughness < 1.0 ? roughness : 1.0 }
	{}

	virtual bool scatter(
		Ray const& incoming_ray,
		HitRecord const& record,
		Double3& attenuation,
		Ray& scattered_ray) const override
	{
		Double3 reflection =
			reflect(incoming_ray.direction.normalized(), record.normal);

		scattered_ray = Ray
		{
			record.position,
			reflection + roughness * randomInUnitSphere()
		};

		attenuation = f_0;
		
		return dot(scattered_ray.direction, record.normal) > 0.0;
	}
};

struct Dielectric : public Material
{
	double index_of_refraction;

	Dielectric(double new_index_of_refraction)
		: index_of_refraction{ new_index_of_refraction }
	{}

	virtual bool scatter(
		Ray const& incoming_ray,
		HitRecord const& record,
		Double3& attenuation,
		Ray& scattered_ray) const override
	{
		attenuation = Double3(1.0, 1.0, 1.0);

		double ratio = record.front_face ?
			(1.0 / index_of_refraction) : index_of_refraction;

		Double3 unit_direction = incoming_ray.direction.normalized();

		double cos_theta = fmin(dot(-unit_direction, record.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = ratio * sin_theta > 1.0;

		Double3 direction;

		if (cannot_refract || fresnelSchlick(cos_theta, ratio) > randomDouble())
		{
			direction = reflect(unit_direction, record.normal);
		}
		else
		{
			direction = refract(unit_direction, record.normal, ratio);
		}

		scattered_ray = Ray{ record.position, direction };

		return true;
	}

	double fresnelSchlick(double cosine, double index) const
	{
		double r_0 = (1.0 - index) / (1.0 + index);

		r_0 *= r_0;

		return r_0 + (1.0 - r_0) * pow((1.0 - cosine), 5.0);
	}
};

#endif // MATERIAL_HPP

