#ifndef RAY_HPP
#define RAY_HPP

#include "math.hpp"

struct Ray
{
	Double3 origin;
	Double3 direction;

	Ray()
	{}

	Ray(Double3 const& new_origin, Double3 const& new_direction)
		: origin{ new_origin }, direction{ new_direction }
	{}

	Double3 at(double t) const
	{
		return origin + t * direction;
	}
};

#endif // RAY_HPP

