#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

// TODO: SIMD operations

struct Double3
{
	double x, y, z;

	Double3()
	{}

	Double3(double new_x, double new_y, double new_z)
		: x{ new_x }, y{ new_y }, z{ new_z }
	{}

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

double dot(Double3 const& d_3_a, Double3 const& d_3_b);
Double3 cross(Double3 const& d_3_a, Double3 const& d_3_b);

#endif // MATH_HPP

