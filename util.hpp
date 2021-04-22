#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <limits>
#include <memory>
#include <random>

constexpr double INF = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
	return degrees * PI / 180.0;
}

inline double randomDouble()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 mersenne_twister;

	return distribution(mersenne_twister);
}

inline double clamp(double d, double min_d, double max_h)
{
	if (d < min_d)
	{
		return min_d;
	}

	if (d > max_h)
	{
		return max_h;
	}
}

void writeColor(std::ostream& os, Double3 const& color, int n_samples_per_pixel)
{
	double scale = 1.0 / n_samples_per_pixel;

	double r = color.x * scale;
	double g = color.y * scale;
	double b = color.z * scale;

	os << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif // UTIL_HPP

