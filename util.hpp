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

inline double randomDouble(double min_d, double max_d)
{
	return min_d + (max_d - min_d) * randomDouble();
}

inline double clamp(double d, double min_d, double max_d)
{
	if (d < min_d)
	{
		return min_d;
	}

	if (d > max_d)
	{
		return max_d;
	}

	return d;
}

#endif // UTIL_HPP

