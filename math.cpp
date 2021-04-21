#include "math.hpp"

double Double3::norm() const
{
	return sqrt(normSquared());
}

double Double3::normSquared() const
{
	return dot(*this, *this);
}

Double3 Double3::operator-() const
{
	return { -x, -y, -z };
}

Double3 Double3::normalized() const
{
	return *this / norm();
}

Double3& Double3::operator+=(double d)
{
	x += d;
	y += d;
	z += d;

	return *this;
}

Double3& Double3::operator-=(double d)
{
	x -= d;
	y -= d;
	z -= d;

	return *this;
}

Double3& Double3::operator*=(double d)
{
	x *= d;
	y *= d;
	z *= d;

	return *this;
}

Double3& Double3::operator/=(double d)
{
	double inverse = 1.0 / d;

	x *= inverse;
	y *= inverse;
	z *= inverse;

	return *this;
}

Double3& Double3::operator+=(Double3 const& d_3)
{
	x += d_3.x;
	y += d_3.y;
	z += d_3.z;

	return *this;
}

Double3& Double3::operator-=(Double3 const& d_3)
{
	x -= d_3.x;
	y -= d_3.y;
	z -= d_3.z;

	return *this;
}

Double3 operator+(double d, Double3 const& d_3)
{
	return { d_3.x + d, d_3.y + d, d_3.z + d };
}

Double3 operator+(Double3 const& d_3, double d)
{
	return { d_3.x + d, d_3.y + d, d_3.z + d };
}

Double3 operator-(double d, Double3 const& d_3)
{
	return { d - d_3.x, d - d_3.y, d - d_3.z };
}

Double3 operator-(Double3 const& d_3, double d)
{
	return { d_3.x - d, d_3.y - d, d_3.z - d };
}

Double3 operator*(double d, Double3 const& d_3)
{
	return { d_3.x * d, d_3.y * d, d_3.z * d };
}

Double3 operator*(Double3 const& d_3, double d)
{
	return { d_3.x * d, d_3.y * d, d_3.z * d };
}

Double3 operator/(double d, Double3 const& d_3)
{
	return { d / d_3.x, d / d_3.y, d };
}

Double3 operator/(Double3 const& d_3, double d)
{
	double inverse = 1.0 / d;

	return { d_3.x * inverse, d_3.y * inverse, d_3.z * inverse };
}

Double3 operator+(Double3 const& d_3_a, Double3 const& d_3_b)
{
	return { d_3_a.x + d_3_b.x, d_3_a.y + d_3_b.y, d_3_a.z + d_3_b.z };
}

Double3 operator-(Double3 const& d_3_a, Double3 const& d_3_b)
{
	return { d_3_a.x - d_3_b.x, d_3_a.y - d_3_b.y, d_3_a.z - d_3_b.z };
}

double dot(Double3 const& d_3_a, Double3 const& d_3_b)
{
	return d_3_a.x * d_3_b.x + d_3_a.y * d_3_b.y + d_3_a.z * d_3_b.z;
}

Double3 cross(Double3 const& d_3_a, Double3 const& d_3_b)
{
	return
	{
		d_3_a.y * d_3_b.z - d_3_a.z * d_3_b.y,
		d_3_a.z * d_3_b.x - d_3_a.x * d_3_b.z,
		d_3_a.x * d_3_b.y - d_3_a.y * d_3_b.x
	};
}

