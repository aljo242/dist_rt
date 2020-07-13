#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

namespace mathLib
{



// constants
constexpr double infinity {std::numeric_limits<double>::infinity()};
constexpr double pi {3.1415926535897932385};


// util fxns
inline double DegreesToRadians(const double degrees)
{
	return degrees * pi / 180.0;
}

inline double RadiansToDegrees(const double radians)
{
	return radians * 180.0 / pi;
}

inline double Clamp(const double x, const double min, const double max)
{
	if(x < min) 
	{
		return min;
	}
	if(x > max) 
	{
		return max;
	}
	
	return x;
}

inline double RandDouble()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double RandDouble(const double min, const double max) // return value in range
{
	return min + (max - min) * RandDouble();
}

inline double RandInt(const int min, const int max)
{
	return static_cast<int>(RandDouble(static_cast<double>(min), static_cast<double>(max+1)));
}

} // namespace mathLib


 
#endif // COMMON_H