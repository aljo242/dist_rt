#ifndef RAY_H
#define RAY_H

#include "vec3.h"

namespace mathLib
{
class ray
{
public:
	ray() = default;
	ray(const point3& o, const vec3& d);
	ray(const point3& o, const vec3& d, const double time);

	inline point3 Origin() const 	{return origin;}
	inline vec3 Direction() const 	{return dir;}
	inline double Time() const 		{return tm;}

	point3 At(const double t) const;

private:
	point3 origin;
	vec3 dir;
	double tm;
};
} // namespace mathLib


#endif