#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <limits>
#include <cmath>

inline float randFloat()
{
	return static_cast<float>(rand() / (RAND_MAX + 1.0));
}

inline float randFloat(const float min, const float max)
{
	return min + (max - min) * randFloat();
}

template <typename T>
inline bool isPerfectSquare(const T x)
{
	const auto sr = static_cast<double>(std::sqrt(x));
	return ((sr - std::floor(sr)) == 0);
}

template <typename T>
bool IsEqual(T rhs, T lhs)
{
	constexpr uint32_t ERROR = 100;

	T diff = std::abs(lhs - rhs);
	T eps = std::numeric_limits<T>::epsilon();
	return diff < (eps* static_cast<T>(ERROR));
}


#endif // UTILS_H