#include "ray.h"

using namespace mathLib;

ray::ray(const vec3& a, const vec3& b)
	:
	A(a),
	B(b)
{}


vec3 ray::point_at_parameter(const float t) const { return A + (B*t); }