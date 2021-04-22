#ifndef MATH_HPP
#define MATH_HPP

#include "util.hpp"

#include <cmath>

// TODO: SIMD operations

struct Double3
{
	double x, y, z;

	inline static Double3 random()
	{
		return
		{
			randomDouble(),
			randomDouble(),
			randomDouble()
		};
	}

	inline static Double3 random(double min_d, double max_d)
	{
		return
		{
			randomDouble(min_d, max_d),
			randomDouble(min_d, max_d),
			randomDouble(min_d, max_d)
		};
	}

	Double3()
	{}

	Double3(double new_x, double new_y, double new_z)
		: x{ new_x }, y{ new_y }, z{ new_z }
	{}

	bool nearZero() const;

	double norm() const;
	double normSquared() const;
	Double3 operator-() const;
	Double3 normalized() const;

	Double3& operator+=(double d);
	Double3& operator-=(double d);
	Double3& operator*=(double d);
	Double3& operator/=(double d);

	Double3& operator+=(Double3 const& d_3);
	Double3& operator-=(Double3 const& d_3);
};

Double3 operator+(double d, Double3 const& d_3);
Double3 operator+(Double3 const& d_3, double d);

Double3 operator-(double d, Double3 const& d_3);
Double3 operator-(Double3 const& d_3, double d);

Double3 operator*(double d, Double3 const& d_3);
Double3 operator*(Double3 const& d_3, double d);

Double3 operator/(double d, Double3 const& d_3);
Double3 operator/(Double3 const& d_3, double d);

Double3 operator+(Double3 const& d_3_a, Double3 const& d_3_b);
Double3 operator-(Double3 const& d_3_a, Double3 const& d_3_b);
Double3 operator*(Double3 const& d_3_a, Double3 const& d_3_b);
Double3 operator/(Double3 const& d_3_a, Double3 const& d_3_b);

double dot(Double3 const& d_3_a, Double3 const& d_3_b);
Double3 cross(Double3 const& d_3_a, Double3 const& d_3_b);

Double3 reflect(Double3 const& d_3_a, Double3 const& d_3_b);
Double3 refract(Double3 const& d_3_a, Double3 const& d_3_b, double ratio);

Double3 randomInUnitSphere();
Double3 randomInUnitDisk();
Double3 randomUnitDouble3();

std::ostream& operator<<(std::ostream& os, Double3 const& d_3);

#endif // MATH_HPP

