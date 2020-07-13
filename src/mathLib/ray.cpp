#include "ray.h"

using namespace mathLib;

ray::ray(const point3& o, const vec3& d)
	: origin(o), dir(d), tm(0.0) {}

ray::ray(const point3& o, const vec3& d, const double time)
	: origin(o), dir(d), tm(time) {}
 

vec3 ray::At(const double t) const { return origin + (dir*t); }