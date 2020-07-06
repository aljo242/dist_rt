#include "camera.h"

using namespace mathLib;
using namespace rtLib;


camera::camera() 
	:
	origin(0.0f, 0.0f, 0.0f),
	lower_left_corner(-2.0f, -1.0f, -1.0f),
	horizontal(4.0f, 0.0f, 0.0f),
	vertical(0.0f, 2.0f, 0.0f)
{}


ray camera::get_ray(const float u, const float v) const
{
	return {origin, lower_left_corner + (u * horizontal) + (v * vertical) - origin};
}