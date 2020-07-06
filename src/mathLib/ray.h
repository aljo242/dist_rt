#ifndef RAY_H
#define RAY_H

#include "vec3.h"

namespace mathLib
{
class ray
{
public:
	ray() = default;
	ray(const vec3& a, const vec3& b);
	inline vec3 origin() const {return A;}
	inline vec3 direction() const {return B;}
	vec3 point_at_parameter(const float t) const;

private:
	vec3 A;
	vec3 B;
};
} // namespace mathLib


#endif