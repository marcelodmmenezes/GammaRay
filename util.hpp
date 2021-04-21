#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>

void writeColor(std::ostream& os, Double3 const& color)
{
	os << static_cast<int>(255.999 * color.x) << ' '
		<< static_cast<int>(255.999 * color.y) << ' '
		<< static_cast<int>(255.999 * color.z) << '\n';
}

#endif // UTIL_HPP

