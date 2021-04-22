#ifndef WRITER_HPP
#define WRITER_HPP

#include "math.hpp"

void writeColor(std::ostream& os, Double3 const& color, int n_samples_per_pixel)
{
	double scale = 1.0 / n_samples_per_pixel;

	/// Rough gamma correction
	double r = sqrt(color.x * scale);
	double g = sqrt(color.y * scale);
	double b = sqrt(color.z * scale);

	os << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';

}

#endif // WRITER_HPP

