#include "math.hpp"
#include "ray.hpp"
#include "util.hpp"

#include <iostream>

int main()
{
	constexpr int width = 256;
	constexpr int height = 256;

	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			Double3 color
			{
				(double)i / (width - 1),
				(double)j / (height - 1),
				0.25
			};

			writeColor(std::cout, color);
		}
	}
}

