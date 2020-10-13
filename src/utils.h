#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

inline float randFloat()
{
	return static_cast<float>(rand() / (RAND_MAX + 1.0));
}

inline float randFloat(const float min, const float max)
{
	return min + (max - min) * randFloat();
}

inline bool isPerfectSquare(const int x)
{
	const auto sr = static_cast<double>(std::sqrt(x));
	return ((sr - std::floor(sr)) == 0);
}


#endif // UTILS_H