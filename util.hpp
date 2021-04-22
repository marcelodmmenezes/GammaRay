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

void writeColor(std::ostream& os, Double3 const& color)
{
	os << static_cast<int>(255.999 * color.x) << ' '
		<< static_cast<int>(255.999 * color.y) << ' '
		<< static_cast<int>(255.999 * color.z) << '\n';
}

#endif // UTIL_HPP

